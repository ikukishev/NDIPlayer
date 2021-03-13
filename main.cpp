#include "PlayerWindow/playerwindow.h"

#include <QApplication>
#include <Processing.NDI.Lib.h>

int main(int argc, char *argv[])
{
    if (!NDIlib_initialize()) return 0;

    // Create a finder
    NDIlib_find_create_t findConfig;
    //findConfig.show_local_sources = true;
    //findConfig.p_groups = "DESKTOP-6EV2Q4G";
    //findConfig.p_extra_ips = "172.16.2.232,172.16.2.9,172.16.1.149";
    NDIlib_find_instance_t pNDI_find = NDIlib_find_create_v2(/*&findConfig*/);
    if (!pNDI_find) return 0;

    // Wait until there is one source

    const NDIlib_source_t* p_sources = NULL;
    auto count = 4;
    while ( count )
    {	// Wait until the sources on the nwtork have changed
        printf("Looking for sources ...\n");
        NDIlib_find_wait_for_sources(pNDI_find, 5000/* One second */);
        uint32_t no_sources = 0;
        p_sources = NDIlib_find_get_current_sources(pNDI_find, &no_sources);
        for (uint32_t i = 0; i < no_sources; ++i)
        {
            printf("stream name: %s, URL: %s\n", p_sources[i].p_ndi_name, p_sources[i].p_url_address );
        }
        --count;
    }

    // We now have at least one source, so we create a receiver to look at it.
    NDIlib_recv_instance_t pNDI_recv = NDIlib_recv_create_v3();
    if (!pNDI_recv) return 0;

    // Connect to our sources
    NDIlib_recv_connect(pNDI_recv, p_sources + 0);



    // Destroy the NDI finder. We needed to have access to the pointers to p_sources[0]
    NDIlib_find_destroy(pNDI_find);

    // Run for one minute
    using namespace std::chrono;
    for (const auto start = high_resolution_clock::now(); high_resolution_clock::now() - start < seconds(10);)
    {	// The descriptors
        NDIlib_video_frame_v2_t video_frame;
        NDIlib_audio_frame_v2_t audio_frame;

        switch (NDIlib_recv_capture_v3(pNDI_recv, &video_frame, nullptr, nullptr, 0))
        {	// No data
            case NDIlib_frame_type_none:
                //printf("No data received.\n");
                break;

            // Video data
            case NDIlib_frame_type_video:
                printf("Video data received (%dx%d).\n", video_frame.xres, video_frame.yres);
                NDIlib_recv_free_video_v2(pNDI_recv, &video_frame);
                break;

            // Audio data
            case NDIlib_frame_type_audio:
                //printf("Audio data received (%d samples).\n", audio_frame.no_samples);
                NDIlib_recv_free_audio_v2(pNDI_recv, &audio_frame);
                break;
        }
    }

    // Destroy the receiver
    NDIlib_recv_destroy(pNDI_recv);

    // Not required, but nice
    NDIlib_destroy();
   QApplication a(argc, argv);
   PlayerWindow w;
   w.show();
   return a.exec();
}
