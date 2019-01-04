package com.ifds.rts;

import java.util.*;
import java.text.*;
import java.io.*;
import java.math.*;

public class RTSTraceWriter
{
    private static PrintWriter _writer;
    private final boolean _verbose;

    private static final NumberFormat _fieldNumberFormat = new DecimalFormat("###0");
    private static final NumberFormat _positionFormat = new DecimalFormat("####0");

    public static final RTSTraceWriter _traceFileWriter;

    private static HashMap mapTraceClientViews = new HashMap(); //format: clientid=viewnum1,viewnum2,... means need to trace the views.
    private static HashMap mapViewThreadNames = new HashMap();

    private static String traceFileName;

    private static SimpleDateFormat logDateFmt = new SimpleDateFormat("yyyyMMdd HHmmss ");
    private static String logHead = "Rts-Api :";

    static
    {
        _fieldNumberFormat.setMinimumIntegerDigits(4);
        _positionFormat.setMinimumIntegerDigits(5);

        RTSTraceWriter tempTraceFileWriter = null;
        traceFileName = System.getProperty( "ifds.rts.tracefile" );

        if ( traceFileName != null && traceFileName.trim().length() >0 )
        {
            tempTraceFileWriter = new RTSTraceWriter(Boolean.getBoolean( "ifds.rts.traceverbose" ));
        }
        _traceFileWriter = tempTraceFileWriter;

    }

    /**
     *
     */
    private RTSTraceWriter( boolean verbose )
    {
        _verbose = verbose;
    }

    //We need to create the writer base on the time...
    private void createWriter()
    {
        if ( traceFileName == null || traceFileName.trim().length()<=0 )
        {
            _writer = null;
            return;
        }

        try
        {
            String logFileName ;

            SimpleDateFormat fileNameDateFmt = new SimpleDateFormat("yyyyMMdd");

            int index = traceFileName.indexOf(".");

            if (index == -1) //not "."
            {
                logFileName = traceFileName + "." + fileNameDateFmt.format(new Date())+".log";
            }
            else
            {
                logFileName = traceFileName.substring(0,index) + "-" + fileNameDateFmt.format(new Date())+traceFileName.substring(index);
            }

            File logFile = new File(logFileName);

            if (!logFile.exists())
            {
                logFile.createNewFile();
                _writer =new PrintWriter( new FileOutputStream( logFileName ), true ) ;
            }
            else
            {
                if (_writer == null)
                {
                    _writer =new PrintWriter( new FileOutputStream( logFileName,true ), true ) ;//use append mode
                }
            }
        }
        catch (Exception any)
        {
            _writer = null;
        }

    }

    public static void setTraceClientViews(String clientId, String views)
    {
        if (clientId==null || clientId.length() <= 0 )
        {
            return;
        }

        if (views== null || views.length()<=0 || views.equalsIgnoreCase("no"))
        {
            mapTraceClientViews.clear();
        }
        else
        {
            mapTraceClientViews.put(clientId,views); //for trace request...
        }

        mapViewThreadNames.clear(); //remove all thread names, so the response will not be trace...
    }

    public static void setCurrentViewThreadName(String viewNum, String viewThreadName)
    {
        mapViewThreadNames.put(viewNum,viewThreadName);
    }

    private static boolean allowedToTraceRequest(String requestBuffer, String viewRequestThreadName)
    {

        if (mapTraceClientViews.size() <=0 || requestBuffer==null || requestBuffer.length()<=0)
        {
            return false;
        }

        Set setClientViews = mapTraceClientViews.entrySet();
        Iterator itClientViews = setClientViews.iterator();

        while ( itClientViews.hasNext() )
        {
            Map.Entry entryClientViews = (Map.Entry) itClientViews.next();

            String clientId = (String)entryClientViews.getKey();
            String views    = (String) entryClientViews.getValue();

            if (views==null || views.length()<=0)
            {
                return false;
            }

            while (views.length() > 0 )
            {
                int index = views.indexOf(",");
                String view = "";
                if (index == -1)
                {
                    view = views;
                    views = "";
                }
                else
                {
                    view = views.substring(0,index);
                    views = views.substring(index+1);
                }

                //System.out.println("!!!!! The view is: " + view + ". views is :" + views);

                if (requestBuffer.indexOf(clientId)!=-1 && requestBuffer.indexOf("00"+view)!=-1)
                {
                    //Now put the view thread name so we can trace the response info...
                    setCurrentViewThreadName(view,viewRequestThreadName);
                    return true;
                }

            }
        }

        return false;
    }

    private static boolean allowedToTraceResponse(String responseBuffer, String viewResponseThreadName)
    {

        if (mapViewThreadNames.size()<=0 || responseBuffer==null || responseBuffer.length()<=0)
        {
            return false;
        }

        Set setClientViews = mapTraceClientViews.entrySet();
        Iterator itClientViews = setClientViews.iterator();

        while ( itClientViews.hasNext() )
        {
            Map.Entry entryClientViews = (Map.Entry) itClientViews.next();

            String clientId = (String)entryClientViews.getKey();
            String views    = (String) entryClientViews.getValue();

            if (views==null || views.length()<=0)
            {
                return false;
            }

            while (views.length() > 0 )
            {
                int index = views.indexOf(",");
                String view = "";
                if (index == -1)
                {
                    view = views;
                    views = "";
                }
                else
                {
                    view = views.substring(0,index);
                    views = views.substring(index+1);
                }

                //System.out.println("!!!!! The view is: " + view + ". views is :" + views);

                String requestViewName = (String)mapViewThreadNames.get(view);

                if (responseBuffer.indexOf("00"+view)!=-1 && viewResponseThreadName.equals(requestViewName) )
                {
                    return true;
                }

            }
        }

        return false;
    }

    public static void traceClientViewsBufferWritten( String buffer, String viewRequestThreadName )
    {
        if (allowedToTraceRequest(buffer, viewRequestThreadName))
        {
            System.out.println("\n");
            System.out.println( "View request buffer written..." );
            System.out.println( buffer );
            System.out.println();
        }
    }

    public static void traceClientViewsResponseRead( String buffer, String viewRespnseThreadName )
    {
        if (allowedToTraceResponse(buffer,viewRespnseThreadName) )
        {
            System.out.println("\n");
            System.out.println( "View response buffer read..." );
            System.out.println( buffer );
            System.out.println("\n");
        }
    }

    /**
     *
     */
    public void close()
    {
        if (_writer!=null)_writer.close();
    }

    /**
     *
     */
    public void traceRequestRead( String buffer )
    {
        createWriter();
        if (_writer!=null)
        {
            _writer.println();
            _writer.println(logDateFmt.format(new Date()) + logHead + " Request buffer read..." );
            _writer.println( buffer );
            _writer.println(logDateFmt.format(new Date()) + logHead + " End of Request buffer read..." );
            _writer.println();
        }
    }

    /**
     *
     */
    public void traceResponseRead( String buffer )
    {
        createWriter();
        if (_writer!=null)
        {
            _writer.println();
            _writer.println(logDateFmt.format(new Date()) + logHead + " Response buffer read..." );
            _writer.println( buffer );
            _writer.println(logDateFmt.format(new Date()) + logHead + " End of Response buffer read..." );
            _writer.println();
        }
    }

    /**
     *
     */
    public void traceBufferWritten( String buffer )
    {
        createWriter();
        if (_writer!=null)
        {
            _writer.println();
            _writer.println(logDateFmt.format(new Date()) + logHead + " Buffer written..." );
            _writer.println( buffer );
            _writer.println(logDateFmt.format(new Date()) + logHead + " End of Buffer written..." );
            _writer.println();
        }
    }

    /**
     *
     */
    public void consoleBufferWritten( String buffer )
    {
        System.out.println();
        System.out.println( "Buffer written..." );
        System.out.println( buffer );
        System.out.println();
    }

    /**
     *
     */
    public void traceDecodeBufferCreated()
    {
        createWriter();
        if (_writer!=null)
        {
            if ( _verbose )
            {
                _writer.println();
                _writer.println( "Decode buffer created..." );
            }
        }
    }

    /**
     *
     */
    public void traceDecodeField( Boolean field )
    {
        createWriter();
        if (_writer!=null)
        {
            if ( _verbose )
            {
                _writer.println( "Decoding Boolean field: " + field );
            }
        }
    }

    /**
     *
     */
    public void traceDecodeField( Date field )
    {
        createWriter();
        if (_writer!=null)
        {
            if ( _verbose )
            {
                _writer.println( "Decoding Date field:    " + field );
            }
        }
    }

    /**
     *
     */
    public void traceDecodeField( Double field )
    {
        createWriter();
        if (_writer!=null)
        {
            if ( _verbose )
            {
                _writer.println( "Decoding Double field:  " + field );
            }
        }
    }

    /**
     *
     */
    public void traceDecodeField( BigDecimal field )
    {
        createWriter();
        if (_writer!=null)
        {
            if ( _verbose )
            {
                _writer.println( "Decoding BigDecimal field:  " + field );
            }
        }

    }

    /**
     *
     */
    public void traceDecodeField( Integer field )
    {
        createWriter();
        if (_writer!=null)
        {
            if ( _verbose )
            {
                _writer.println( "Decoding Integer field: " + field );
            }
        }
    }

    /**
     *
     */
    public void traceDecodeField( String field )
    {
        createWriter();
        if (_writer!=null)
        {
            if ( _verbose )
            {
                _writer.println( "Decoding String field:  " + field );
            }
        }

    }

    /**
     *
     */
    public void traceEncodeBufferCreated()
    {
        createWriter();
        if (_writer!=null)
        {
            if ( _verbose )
            {
                _writer.println();
                _writer.println( "Encode buffer created..." );
            }
        }
    }

    /**
     *
     */
    public void traceEncodeField( Boolean field )
    {
        createWriter();
        if (_writer!=null)
        {
            if ( _verbose )
            {
                _writer.println( "Encoding Boolean field: " + field );
            }
        }
    }

    /**
     *
     */
    public void traceEncodeField( Date field )
    {
        createWriter();
        if (_writer!=null)
        {
            if ( _verbose )
            {
                _writer.println( "Encoding Date field:    " + field );
            }
        }
    }

    /**
     *
     */
    public void traceEncodeField( Double field )
    {
        createWriter();
        if (_writer!=null)
        {
            if ( _verbose )
            {
                _writer.println( "Encoding Double field:  " + field );
            }
        }
    }

    /**
     *
     */
    public void traceEncodeField( BigDecimal field )
    {
        createWriter();
        if (_writer!=null)
        {
            if ( _verbose )
            {
                _writer.println( "Encoding BigDecimal field:  " + field );
            }
        }
    }

    /**
     *
     */
    public void traceEncodeField( Integer field )
    {
        createWriter();
        if (_writer!=null)
        {
            if ( _verbose )
            {
                _writer.println( "Encoding Integer field: " + field );
            }
        }
    }

    /**
     *
     */
    public void traceEncodeField( String field )
    {
        createWriter();
        if (_writer!=null)
        {
            if ( _verbose )
            {
                _writer.println( "Encoding String field:  " + field );
            }
        }
    }

}
