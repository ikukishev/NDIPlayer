#include "PlayerWindow/playerwindow.h"

#include <QApplication>
#include <Processing.NDI.Lib.h>

int main(int argc, char *argv[])
{
   QApplication a(argc, argv);
   PlayerWindow w;
   w.show();
   return a.exec();
}
