#include <QtCore>

void WriteTs(QFile & File,QString filename)
{
  QFile F ( filename )                             ;
  if ( ! F . open ( QIODevice::ReadOnly ) ) return ;
  bool       drop = false                          ;
  QByteArray L                                     ;
  QString    E = "</TS>"                           ;
  QString    S                                     ;
  L = F . readLine ( )                             ;
  L = F . readLine ( )                             ;
  L = F . readLine ( )                             ;
  do                                               {
    L = F . readLine ( )                           ;
    if ( L . size ( ) > 0 )                        {
      S = QString::fromUtf8 ( L )                  ;
      S = S . replace ( "\r" , "" )                ;
      S = S . replace ( "\n" , "" )                ;
      if ( S == E ) drop = true                    ;
    } else drop = true                             ;
    if ( ! drop ) File . write ( L )               ;
  } while ( ! drop )                               ;
  F . close ( )                                    ;
}

int main(int argc,char ** argv)
{
  if ( argc < 5 ) return 0                                             ;
  QStringList Ts                                                       ;
  QString     Lc = argv [ 1 ]                                          ;
  QString     Ss = argv [ 2 ]                                          ;
  QFile       F ( Ss )                                                 ;
  for (int i=3;i<argc;i++) Ts << argv [ i ]                            ;
  if ( F . open ( QIODevice::WriteOnly ) )                             {
    QStringList Header                                                 ;
    QString     H                                                      ;
    Header << "<?xml version=\"1.0\" encoding=\"utf-8\"?>"             ;
    Header << "<!DOCTYPE TS>"                                          ;
    Header << QString ("<TS version=\"2.0\" language=\"%1\">").arg(Lc) ;
    H = Header . join ( "\r\n" )                                       ;
    F . write ( H . toUtf8 ( ) )                                       ;
    H = "\r\n"                                                         ;
    F . write ( H . toUtf8 ( ) )                                       ;
    foreach ( H , Ts ) WriteTs ( F , H )                               ;
    H = "</TS>"                                                        ;
    F . write ( H . toUtf8 ( ) )                                       ;
    H = "\r\n"                                                         ;
    F . write ( H . toUtf8 ( ) )                                       ;
    F . close (                )                                       ;
  }                                                                    ;
  return 1                                                             ;
}
