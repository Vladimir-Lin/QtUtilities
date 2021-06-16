#include <QtCore>


QFileInfoList FileInfos(QDir & dir)
{
  QFileInfoList fi = dir.entryInfoList(QDir::AllEntries|QDir::NoDotAndDotDot) ;
  QFileInfoList target                                                        ;
  for (int i=0;i<fi.size();)                                                  {
    if ("." ==fi[i].fileName()) fi.removeAt(i) ;                           else
    if (".."==fi[i].fileName()) fi.removeAt(i) ;                           else
    i++                                                                       ;
  }                                                                           ;
  target = fi                                                                 ;
  for (int i=0;i<fi.size();i++) if (fi[i].isDir())                            {
    QDir d(fi[i].absoluteFilePath())                                          ;
    QFileInfoList ni                                                          ;
    ni = FileInfos(d)                                                         ;
    target += ni                                                              ;
  }                                                                           ;
  return target                                                               ;
}

QFileInfoList GetFiles(void)
{
  QDir d = QDir::current ( ) ;
  return FileInfos ( d )     ;
}

QString RemoveCC(QString c)
{
  QString r                           ;
  int     i = 0                       ;
  int     L = c . length ( )          ;
  bool    w = true                    ;
  while ( i < L )                     {
    QChar p = c . at ( i )            ;
    if ( w )                          {
      if ( p == QChar ( '/' ) )       {
        QString X = c . mid ( i , 2 ) ;
        if ( "/*" == X )              {
          i += 2                      ;
          w  = false                  ;
        }                             ;
      }                               ;
      if ( w )                        {
        r += p                        ;
        i++                           ;
      }                               ;
    } else                            {
      if ( p == QChar ( '*' ) )       {
        QString X = c . mid ( i , 2 ) ;
        if ( "*/" == X )              {
          i += 2                      ;
          w  = true                   ;
        } else i++                    ;
      } else i++                      ;
    }                                 ;
  }                                   ;
  return r                            ;
}

QString RemoveCCC(QString c)
{
  QString r                           ;
  int     i = 0                       ;
  int     L = c . length ( )          ;
  bool    w = true                    ;
  while ( i < L )                     {
    QChar p = c . at ( i )            ;
    if ( w )                          {
      if ( p == QChar ( '/' ) )       {
        QString X = c . mid ( i , 2 ) ;
        if ( "//" == X )              {
          i += 2                      ;
          w  = false                  ;
        }                             ;
      }                               ;
      if ( w )                        {
        r += p                        ;
        i++                           ;
      }                               ;
    } else                            {
      if ( p == QChar ( '\r' ) )      {
        w  = true                     ;
        r += p                        ;
      } else
      if ( p == QChar ( '\n' ) )      {
        w  = true                     ;
        r += p                        ;
      } else i++                      ;
    }                                 ;
  }                                   ;
  return r                            ;
}

QString GetHpp(QString filename)
{
  QFile F ( filename )                                ;
  if ( ! F . open ( QIODevice::ReadOnly ) ) return "" ;
  QByteArray B = F . readAll ( )                      ;
  F . close ( )                                       ;
  return QString::fromUtf8 ( B )                      ;
}

bool SaveHpp(QString filename,QByteArray & B)
{
  QFile F ( filename )                                    ;
  if ( ! F . open ( QIODevice::WriteOnly ) ) return false ;
  F . write ( B )                                         ;
  F . close (   )                                         ;
  return true                                             ;
}

int main(int argc,char * argv[])
{
  QFileInfoList files                              ;
  QFileInfo     f                                  ;
  //////////////////////////////////////////////////
  if ( argc > 1 )                                  {
    for (int i = 1 ; i < argc ; i++ )              {
      QString s = QString::fromUtf8 ( argv [ i ] ) ;
      QFileInfo fs ( s )                           ;
      files << fs                                  ;
    }                                              ;
  } else                                           {
    files = GetFiles ( )                           ;
  }                                                ;
  //////////////////////////////////////////////////
  foreach ( f , files ) if ( f . exists ( ) )      {
    QString bn = f . suffix ( ) . toLower ( )      ;
    bool    cc = false                             ;
    if ( "h"   == bn ) cc = true                   ;
    if ( "hh"  == bn ) cc = true                   ;
    if ( "hpp" == bn ) cc = true                   ;
    if ( cc )                                      {
      QString    ff = f  . absoluteFilePath ( )    ;
      QByteArray BB = ff . toUtf8           ( )    ;
      QString    hh                                ;
      printf ( "%s\r\n" , BB . constData ( ) )     ;
      hh = GetHpp      ( ff      )                 ;
      hh = RemoveCC    ( hh      )                 ;
      hh = RemoveCCC   ( hh      )                 ;
      BB = hh . toUtf8 (         )                 ;
      SaveHpp          ( ff , BB )                 ;
    }                                              ;
  }                                                ;
  //////////////////////////////////////////////////
  return 0                                         ;
}
