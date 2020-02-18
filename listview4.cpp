#include <gtkmm.h>

// 派生レコードクラス
class MyRecord : public Gtk::TreeModel::ColumnRecord
{

public:
    Gtk::TreeModelColumn< Glib::RefPtr< Gdk::Pixbuf > >  m_col_image;
    Gtk::TreeModelColumn< Glib::ustring > m_col_name;

    MyRecord(){

        // レコード( Gtk::TreeModel::ColumnRecord )に列( Gtk::TreeModelColumn )を登録
        add( m_col_image );
        add( m_col_name );
    }
};

class CellRenderer_ValueBase : public Gtk::CellRendererText
{
public:
	CellRenderer_ValueBase();
	~CellRenderer_ValueBase(){};

	virtual void
	render_vfunc(
		const ::Cairo::RefPtr< ::Cairo::Context>& cr,
		Gtk::Widget& widget,
		const Gdk::Rectangle& background_area,
		const Gdk::Rectangle&  cell_area,
		Gtk::CellRendererState flags);

    Glib::RefPtr<Gdk::Pixbuf> m_pixbuf;
};

CellRenderer_ValueBase::CellRenderer_ValueBase(){
};

void
CellRenderer_ValueBase::render_vfunc(
	const    ::Cairo::RefPtr< ::Cairo::Context>& cr,
	      Gtk::Widget&           widget,
	const Gdk::Rectangle&        background_area,
	const Gdk::Rectangle&        ca /*cell_areai*/,
	      Gtk::CellRendererState flags)
{
	if (!cr)
		return;
	const int height(ca.get_height());
	const int width(ca.get_width());

    printf("[TTT]w:h= %d:%d \n", width, height); 
    if(!m_pixbuf) {
        /* Glib::RefPtr<Gdk::Pixbuf>*/
        //m_pixbuf = Gdk::Pixbuf::create_from_file("apple-red.png");
        m_pixbuf = Gdk::Pixbuf::create_from_file("/home/comm/work/gtkmm/study/pixbufzz/frost.png");
    //printf("[TTT] %s:%d <%s>\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
 
    }else{

//        Gdk::Cairo::set_source_pixbuf(cr, m_pixbuf, 0, 0);
//=        cr->set_source_rgb(1.0, 1.0, 1.0);
//-        cr->rectangle(100, 50, m_pixbuf->get_width()*5, m_pixbuf->get_height()*5);
        //cr->paint();
//-        cr->fill();
        printf("[TTT]w:h= %d:%d \n", m_pixbuf->get_width(), m_pixbuf->get_height());

    }
//   	cr->set_source_rgb(1.0, 1.0, 1.0);
//    cr->rectangle(ca.get_x()+1, ca.get_y()+1, width-3, height-3);
//    cr->stroke();

//    cr->set_source_rgb(0.0, 0.0, 0.0);
//    cr->rectangle(ca.get_x(), ca.get_y(), width-1, height-1);
//    cr->stroke();
    printf("[TTT]----------x:y= %d:%d \n", ca.get_x(), ca.get_y()); 
if(0) {
//if(ca.get_x()>48) {
    Gdk::Cairo::set_source_pixbuf( cr, m_pixbuf->scale_simple( 154, 48, Gdk::INTERP_NEAREST ), 51, 49 );
    //Gdk::Cairo::set_source_pixbuf( cr, m_pixbuf->scale_simple( 20, 48/12, Gdk::INTERP_NEAREST ), 101, 0 );
    //cr->fill();
    cr->paint();
}
}


/////////////////////


class MainWin : public Gtk::Window
{
    Gtk::ScrolledWindow m_scrwin;
    Gtk::TreeView m_treeview;

    MyRecord m_record;
    Glib::RefPtr< Gtk::ListStore > m_liststore;

public:
    MainWin();
};


MainWin::MainWin()
{
    // レコードを用いてモデル( Gtk::ListStore )作成
    m_liststore = Gtk::ListStore::create( m_record );

    // モデルをビュー( Gtk::TreeView )にセット
    m_treeview.set_model( m_liststore );

    // ビューの列クラス(Gtk::TreeViewColumn)を作ってTreeViewに登録
    Gtk::TreeViewColumn* viewcol = Gtk::manage( new Gtk::TreeViewColumn( "アイコン+名前" ) );
    m_treeview.append_column( *viewcol );

    // pixbufのレンダリングクラス(Gtk::CellRendererPixbuf)を作って
    // ビューの列クラス(Gtk::TreeViewColumn)にパック
    Gtk::CellRendererPixbuf* ren_pixbuf = Gtk::manage( new Gtk::CellRendererPixbuf() );
    ren_pixbuf->property_pixbuf()= Gdk::Pixbuf::create_from_file("/home/comm/work/gtkmm/study/pixbufzz/frost.png");
    viewcol->pack_start( *ren_pixbuf, false );
    // pixbufの実体が登録されているモデルの列を指定。0 はモデルの0列目(m_col_image)の意味
    viewcol->add_attribute( *ren_pixbuf, "pixbuf", 0 ); 

    // テキストレンダリングクラス(Gtk::CellRendererText)を作って
    // ビューの列クラス(Gtk::TreeViewColumn)にパック
    CellRenderer_ValueBase* ren_text = Gtk::manage( new CellRenderer_ValueBase() );
    //Gtk::CellRendererText* ren_text = Gtk::manage( new Gtk::CellRendererText() );
    viewcol->pack_start( *ren_text, true );
    // テキストの実体が登録されているモデルの列を指定。1 はモデルの1列目(m_col_text)の意味
    viewcol->add_attribute( *ren_text, "text", 1 ); 

    // モデルに行を追加するとビューの表示も同時に更新される
    Gtk::TreeModel::Row row;

    row = *( m_liststore->append() );
        // Gtk::Widget::render_icon()を使ってストックアイコンをレンダリングする
        row[ m_record.m_col_image ] = ren_pixbuf->property_pixbuf(); //Gtk::Widget::render_icon_pixbuf( Gtk::Stock::YES, Gtk::ICON_SIZE_DIALOG );
    //row[ m_record.m_col_image ] = Gtk::Widget::render_icon_pixbuf( Gtk::Stock::YES, Gtk::ICON_SIZE_MENU );
    //row[ m_record.m_col_name ] = "ほげ";

    row = *( m_liststore->append() );
    //row[ m_record.m_col_image ] = Gtk::Widget::render_icon_pixbuf( Gtk::Stock::NO, Gtk::ICON_SIZE_DIALOG);
    ren_pixbuf->property_pixbuf()= Gdk::Pixbuf::create_from_file("/home/comm/work/gtkmm/study/pixbufzz/byouri008.jpg");
    row[ m_record.m_col_image ] = ren_pixbuf->property_pixbuf();//Gtk::Widget::render_icon_pixbuf( Gtk::Stock::NO, Gtk::ICON_SIZE_DIALOG);
    row[ m_record.m_col_name ] = "あああ";
#if 0
    Glib::RefPtr<Gdk::Pixbuf> pixbuf = Gdk::Pixbuf::create_from_file("apple-red.png");
    Gtk::DrawingArea myArea;
//    Cairo::RefPtr<Cairo::Context> myContext = get_window()->create_cairo_context();
//    myContext->set_source_rgb(1.0, 0.0, 0.0);
//    myContext->set_line_width(2.0);

#endif
    // widgetのパック
    m_scrwin.add( m_treeview );
    add( m_scrwin );
    show_all_children();
    resize( 200,200 );
}


int main( int argc, char *argv[] )
{
    Gtk::Main kit( argc, argv );
    MainWin mainwin;
    Gtk::Main::run( mainwin );

    return 0;
}

// https://www.hakodate-ct.ac.jp/~tokai/tokai/gtkmm/begin/p40.htm
// g++ listview4.cpp -o listview4 `pkg-config gtkmm-3.0 --cflags --libs`

