#include "mkapp.h"

MKApp::MKApp(int &argc, char **argv)
    :QApplication(argc, argv)
{

}
//return true --- success
bool MKApp::LoadSettings()
{
    return true;
}
