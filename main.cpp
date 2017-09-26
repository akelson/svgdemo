#include <QApplication>
#include <QSvgRenderer>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsSvgItem>
#include <QGraphicsItemAnimation>
#include <QtXml>
#include <QTimeLine>

int main( int argc, char* argv[] )
{
    QApplication app( argc, argv );

    QSvgRenderer* p_render = new QSvgRenderer();
    p_render->load( QString( "svg/test.svg" ) );

    QTimeLine* p_timer = new QTimeLine( 100000 );
    p_timer->setFrameRange( 0, 100 );

    QGraphicsScene scene;
    scene.setSceneRect( -500, -250, 1000, 500 );

    const int num_obj = 100;
    for ( int i = 0; i < num_obj; i ++ )
    {
        QGraphicsSvgItem* p_item = new QGraphicsSvgItem();

        p_item->setElementId( "foo" );
        p_item->setSharedRenderer( p_render );
        p_item->setRotation( i );
        p_item->setScale( 1 - double ( i ) / num_obj );

        QGraphicsItemAnimation* p_animation = new QGraphicsItemAnimation;
        p_animation->setItem( p_item );
        p_animation->setTimeLine( p_timer );
        const double speed = 1 - 20 * double( i ) / 100;
        for ( int j = 0; j < 200; j++ )
        {
            p_animation->setRotationAt( double( j ) / 200, 1 - speed * double( j ) );
        }

        scene.addItem( p_item );
    } // end for

    QGraphicsView view( &scene );
    view.show();
    p_timer->start();
    app.exec();
} // end main
