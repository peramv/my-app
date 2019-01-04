/*
 * JFC application.
 *
 * This JFC application extends the javax.swing.JFrame class by
 * creating a main window with a basic menu bar and toolbar.
 */

import com.ifds.stubEditor.SeMainPanel;
import com.ifds.stubEditor.data.*;
import java.text.ParseException;
import java.io.*;                    
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class StubEditor extends JFrame implements ActionListener
{
//   private static final String FILE_ENCODING = "UTF-8";

   public StubEditor( int transactionID, boolean request, String encoding ) throws InstantiationException
   {
      _encoding = encoding;
      init();

      if (request)
         _stubData = SeRequestData.fromTransactionId( transactionID );
      else
         _stubData = SeResponseData.fromTransactionId( transactionID );

      _mainPanel = new SeMainPanel( _stubData );
      getContentPane().add(BorderLayout.CENTER, _mainPanel);
   }

   public StubEditor( File file, String encoding ) throws ParseException, IOException, InstantiationException
   {
      _encoding = encoding;
      init();
      _stubData = SeStubData.fromStubFile( file, _encoding );
      _mainPanel = new SeMainPanel( _stubData );
      getContentPane().add(BorderLayout.CENTER, _mainPanel);

   }

   private void init() throws InstantiationException
   {
      
      // Initialize
      //
      // Common images for menubar and toolbar
      iconSave  = new ImageIcon("images/save.gif");
      iconAbout = new ImageIcon("images/about.gif");

      // Frame
      setTitle("RTS Stub Data Editor");
      setDefaultCloseOperation(JFrame.DO_NOTHING_ON_CLOSE);
      getContentPane().setLayout(new BorderLayout(0,0));
      setBounds( 20, 20, 900, 600 );
      setVisible(false);

      // Menu
      menuMain = new JMenuBar();
      setJMenuBar(menuMain);
      menuAddItems(menuMain);

      panel2 = new JPanel(new FlowLayout(FlowLayout.LEFT,0,0));
      getContentPane().add(BorderLayout.NORTH, panel2);
//      panel2.setBounds(0,0,475,30);

      // Toolbar
      _toolBar = new JToolBar();
      panel2.add(_toolBar);
//      _toolBar.setBounds(0,0,375,30);
      tbAddButtons(_toolBar);

      // Save file dialogs
      saveFileDialog = new FileDialog(this,"Save",FileDialog.SAVE);
      saveFileDialog.setModal(true);

      // Register listeners
      //
      // Window listener
      this.addWindowListener(
         new WindowAdapter()
         {
            public void windowClosing(WindowEvent event)
            {
               Object object = event.getSource();
               if ( object == StubEditor.this )
               {
                  ExitApplication( event );
               }
            }
         } );

      // Menu and toolbar listener
      menuitemSave.addActionListener(this);
      menuitemSaveAs.addActionListener(this);
      menuitemExit.addActionListener(this);
      menuitemAbout.addActionListener(this);
      buttonSave.addActionListener(this);
      buttonAbout.addActionListener(this);
   }

   protected void tbAddButtons(JToolBar toolbar)
   {
      Rectangle bounds = new Rectangle();
      // Bounds for each button
      bounds.x=2;
      bounds.y=2;
      bounds.width=25;
      bounds.height=25;
      // Toolbar separator
      Dimension separator = new Dimension(5,5);
      // Button size
      Dimension buttonsize = new Dimension(bounds.width,bounds.height);

      // Save
      buttonSave = new JButton(iconSave);
      buttonSave.setDefaultCapable(false);
      buttonSave.setToolTipText("Save the active document");
      buttonSave.setMnemonic((int)'S');
      toolbar.add(buttonSave);
      buttonSave.setBounds(bounds);
      buttonSave.setMinimumSize(buttonsize);
      buttonSave.setMaximumSize(buttonsize);
      buttonSave.setPreferredSize(buttonsize);
      // Separator
      toolbar.addSeparator(separator);
      // About
      buttonAbout = new JButton(iconAbout);
      buttonAbout.setDefaultCapable(false);
      buttonAbout.setToolTipText("Display program information");
      buttonAbout.setMnemonic((int)'A');
      toolbar.add(buttonAbout);
      bounds.x += bounds.width;
      buttonAbout.setBounds(bounds);
      buttonAbout.setMinimumSize(buttonsize);
      buttonAbout.setMaximumSize(buttonsize);
      buttonAbout.setPreferredSize(buttonsize);
   }

   protected void menuAddItems(JMenuBar hmenu)
   {
      JMenu menu;
      JMenuItem item;

      //
      // "File" menu
      //
      menu = new JMenu("File");
      menu.setActionCommand("File");
      menu.setBorderPainted(false);
      menu.setMnemonic((int)'F');
      hmenu.add(menu);
      // "Save" item
      menuitemSave = new JMenuItem("Save");
      menuitemSave.setHorizontalTextPosition(SwingConstants.RIGHT);
      menuitemSave.setActionCommand("Save");
      menuitemSave.setBorderPainted(false);
      menuitemSave.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_S, Event.CTRL_MASK));
      menuitemSave.setMnemonic((int)'S');
      menuitemSave.setIcon(iconSave);
      menu.add(menuitemSave);
      // "Save As" item
      menuitemSaveAs = new JMenuItem("Save As...");
      menuitemSaveAs.setActionCommand("Save As...");
      menuitemSaveAs.setBorderPainted(false);
      menuitemSaveAs.setMnemonic((int)'A');
      menu.add(menuitemSaveAs);
      // Separator
      menu.add(new JSeparator());
      // "Exit" item
      menuitemExit = new JMenuItem("Exit");
      menuitemExit.setActionCommand("Exit");
      menuitemExit.setBorderPainted(false);
      menuitemExit.setMnemonic((int)'X');
      menu.add(menuitemExit);
      //
      // "Help" menu
      //
      menu = new JMenu("Help");
      menu.setActionCommand("Help");
      menu.setBorderPainted(false);
      menu.setMnemonic((int)'H');
      hmenu.add(menu);
      // "About" item
      menuitemAbout = new JMenuItem("About...");
      menuitemAbout.setHorizontalTextPosition(SwingConstants.RIGHT);
      menuitemAbout.setActionCommand("About...");
      menuitemAbout.setBorderPainted(false);
      menuitemAbout.setMnemonic((int)'A');
      menuitemAbout.setIcon(iconAbout);
      menu.add(menuitemAbout);
   }

   /**
    * The entry point for this application.
    */
   static public void main(String args[])
   {
      try
      {
         try
         {
            UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
         }
         catch ( Exception e )
         {
         }

         if ( args.length == 2 || args.length == 3 )
         {
            if ( args[0].equals("file") )
            {
               (new StubEditor( new File(args[1]), args.length==3?args[2]:"UTF-8" ) ).setVisible(true);
            }
            else if ( args[0].equals("request") )
            {
               (new StubEditor( Integer.parseInt(args[1]), true, args.length==3?args[2]:"UTF-8" ) ).setVisible(true);
            }
            else if ( args[0].equals("response") )
            {
               (new StubEditor( Integer.parseInt(args[1]), false, args.length==3?args[2]:"UTF-8" ) ).setVisible(true);
            }
            else
            {
               printUsage();
               System.exit(1);
            }
         }
         else
         {
            printUsage();
            System.exit(1);
         }
         
      
      }
      catch ( Exception e )
      {
//         System.err.println(e);
         e.printStackTrace();
         System.exit(1);
      }
   }

   private static void printUsage()
   {
      System.out.println();
      System.out.println("Usages:" );
      System.out.println();
      System.out.println("Open existing file -");
      System.out.println("   java StubEditor file <filename> [<encoding>]" );
      System.out.println();
      System.out.println("Create new request -");
      System.out.println("   java StubEditor request <transid> [<encoding>]" );
      System.out.println();
      System.out.println("Create new response -");
      System.out.println("   java StubEditor response <transid> [<encoding>]" );
      System.out.println();
      System.out.println("Where -");
      System.out.println("   <filename>   - filename of a existing request or response file.");
      System.out.println("   <transid>    - transaction identifier of the request/response to be created.");
      System.out.println("   <encoding>   - character encoding for text fields in the opened/created file");
      System.out.println("                  (eg. ISO8859-1, UTF-8).  If unspecified, UTF-8 is assumed.");
   }

   // Used by addNotify
   boolean addNotify_done=false;

   /** 
    * Makes this Container displayable by connecting it to
    * a native screen resource.  Making a container displayable will
    * cause any of its children to be made displayable.
    * This method is called internally by the toolkit and should
    * not be called directly by programs.
    * <p>
    * Overridden here to adjust the size of the frame if needed.
    * </p>
    * @see java.awt.Component#isDisplayable
    * @see java.awt.Container#removeNotify
    */
   public void addNotify()
   {
      Dimension d=getSize();

      super.addNotify();

      if ( addNotify_done ) return;

      // Adjust size according to the insets so that entire component
      // areas are renderable.
      int menubarheight=0;
      JMenuBar menubar = getRootPane().getJMenuBar();
      if ( menubar!=null )
      {
         menubarheight = menubar.getPreferredSize().height;
      }
      Insets insets=getInsets();
      setSize(insets.left + insets.right + d.width, insets.top + insets.bottom + d.height + menubarheight);
      addNotify_done=true;
   }

   // Declarations
   //

   String _encoding;
   // StubData
   SeStubData _stubData;

   // Panels
   JPanel panel2;
   SeMainPanel _mainPanel;

   // Main menubar
   JMenuBar menuMain;
   // "File" menu
   JMenuItem menuitemSave;
   JMenuItem menuitemSaveAs;
   JMenuItem menuitemExit;
   // "Help" menu
   JMenuItem menuitemAbout;
   // Main toolbar
   JToolBar _toolBar;
   JButton buttonSave;
   JButton buttonAbout;
   // Save file dialogs
   FileDialog saveFileDialog;
   // Images
   ImageIcon iconSave;
   ImageIcon iconAbout;

   protected void AboutApplication()
   {
      try
      {
         JOptionPane.showMessageDialog(this,
                                       "RTS Stub Data Editor",
                                       "About" ,
                                       JOptionPane.INFORMATION_MESSAGE);
      }
      catch ( Exception e )
      {
      }
   }

   protected void ExitApplication( AWTEvent event )
   {
      try
      {
         if ( _stubData.isDirty() )
         {
            
            // Beep
            Toolkit.getDefaultToolkit().beep();
            // Show an Exit confirmation dialog
            int reply = JOptionPane.showConfirmDialog(this,
                                                      "Do you wish to save the respones?",
                                                      "Exit" ,
                                                      JOptionPane.YES_NO_CANCEL_OPTION,
                                                      JOptionPane.QUESTION_MESSAGE);
            if ( reply==JOptionPane.CANCEL_OPTION )
            {
               return;
            }
            else if ( reply==JOptionPane.YES_OPTION )
            {
               saveAction( event );
            }
         }

         this.setVisible(false);
         this.dispose();
         System.exit(0);

      }
      catch ( Exception e )
      {
      }
   }

   public void actionPerformed(ActionEvent event)
   {
      Object object = event.getSource();
      if ( object==menuitemSave || object==buttonSave )
      {
         saveAction(event);
      }
      else if ( object==menuitemSaveAs )
      {
         saveAsAction(event);
      }
      else if ( object==menuitemExit )
      {
         exitAction(event);
      }
      else if ( object==menuitemAbout || object==buttonAbout )
      {
         aboutAction(event);
      }
   }

   void saveAction(AWTEvent event)
   {
      if ( !_stubData.hasValidFile() )
      {
         saveAsAction( event );
      }
      else
      {
         try
         {
            _stubData.save();
         }
         catch ( Exception e )
         {
            System.err.println( e.toString() );
            e.printStackTrace();
         }
      }
   }

   void saveAsAction(AWTEvent event)
   {

      try
      {
         // Show saveFileDialog modal
         saveFileDialog.setVisible(true);
         if ( saveFileDialog.getFile() != null )
         {
            _stubData.saveAs( new File( saveFileDialog.getDirectory(), saveFileDialog.getFile() ), _encoding );
         }
      }
      catch ( Exception e )
      {
         System.err.println( e.toString() );
         e.printStackTrace();
      }

   }

   void exitAction(AWTEvent event)
   {

      // TODO:  code goes here

      try
      {
         this.ExitApplication( event );
      }
      catch ( Exception e )
      {
      }
   }

   void aboutAction(AWTEvent event)
   {

      // TODO:  code goes here

      try
      {
         this.AboutApplication();
      }
      catch ( Exception e )
      {
      }
   }

}
