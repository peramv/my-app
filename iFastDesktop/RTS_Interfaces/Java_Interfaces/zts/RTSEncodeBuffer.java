package com.ifds.rts;

import java.text.SimpleDateFormat;
import java.text.DecimalFormat;
import java.util.Date;
import java.io.*;
import java.math.*;

/**
 * <p>RTSEncodeBuffer provides an abstract base class for
 * all encodable RTS buffers. It provides the base class
 * for RTSRequestEncodeBuffer and RTSResponseEncodeBuffer,
 * providing common methods for encoding header and
 * non-header fields.</p>
 * <p>All constructors are of package scope so that
 * other packages cannot add specializations.</p>
 */
public abstract class RTSEncodeBuffer implements RTSBuffer
{

    /**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private final SimpleDateFormat dateFmt = new SimpleDateFormat("MMddyyyy");   //Simple date format cannot be made static
    private static final DecimalFormat deciFmt = new DecimalFormat("#0.00##");    //can be static

    private static byte[] TRUE_FIELD_BYTES = { 'Y'};
    private static byte[] FALSE_FIELD_BYTES = { 'N'};

    private String _encoding;
    private final ByteArrayOutputStream _outByteStream;
    private boolean _firstField = true;
    
//    private String separator = System.getProperty("SEPARATOR")!=null? System.getProperty("SEPARATOR") : ",";
    private String separator = "\u00fe";
//    private String separator = "þ";

    /**
     *
     */
    RTSEncodeBuffer( String encoding )
    {
        _encoding = encoding;
        _outByteStream = new ByteArrayOutputStream(1024);
    
        if ( RTSTraceWriter._traceFileWriter != null )
           RTSTraceWriter._traceFileWriter.traceEncodeBufferCreated();
    }

    /**
     *
     */
    protected final void appendHeaderField( String headerField ) throws UnsupportedEncodingException
    {
        try
        {
            _outByteStream.write( headerField.getBytes( "ISO8859-1" ) );
        }
        catch ( UnsupportedEncodingException e )
        {
            throw e;
        }
        catch ( IOException e )
        {
            throw new UnexpectedByteIOException(e);
        }
    }

    /**
     *
     */
    private final void appendEncodedField( byte[] fieldBytes ) throws UnsupportedEncodingException
    {
        try
        {
            if ( _firstField )
                _firstField = false;
            else
                _outByteStream.write( separator.charAt(0) );

            _outByteStream.write( 'F' );
            _outByteStream.write( fieldBytes );
        }
        catch ( UnsupportedEncodingException e )
        {
            throw e;
        }
        catch ( IOException e )
        {
            throw new UnexpectedByteIOException(e);
        }

    }

    /**
     *
     */
//   private final void appendEncodedField( String field ) throws UnsupportedEncodingException
//   {
//      appendEncodedField( field.getBytes( _encoding ) );
//   }

    /**
     *
     */
    private final void appendUnknownField() 
    {
        if ( _firstField )
            _firstField = false;
        else
            _outByteStream.write( separator.charAt(0) );

        _outByteStream.write( 'T' );

    }


    /**
     * <p>This method encodes the given Boolean value into
     * an RTS logical field, and appends it to the end of the buffer.</p>
     * <p>If the Boolean value is null, the field will be encoded
     * as "null field". Typically this will result in the host
     * database storing a database null for this field.</p>
     * 
     * @param val
     */
    public final void appendField(Boolean val) throws UnsupportedEncodingException
    {

        if ( RTSTraceWriter._traceFileWriter != null )
           RTSTraceWriter._traceFileWriter.traceEncodeField( val );

        if ( val == null )
            appendUnknownField();
        else if ( val.booleanValue() == true )
            appendEncodedField( TRUE_FIELD_BYTES );
        else
            appendEncodedField( FALSE_FIELD_BYTES );

    }

    /**
     * <p>This method encodes the given Date value into
     * and RTS date field, and appends it to the end of the buffer.</p>
     * <p>If the Date value is null, the field will be encoded
     * as "null field". Typically this will result in the host
     * database storing a database null for this field.</p>
     * 
     * @param val
     */
    public final void appendField(Date val) throws UnsupportedEncodingException
    {

        if ( RTSTraceWriter._traceFileWriter != null )
           RTSTraceWriter._traceFileWriter.traceEncodeField( val );

        if ( val == null )
            appendUnknownField();
        else
            appendEncodedField( dateFmt.format(val).toString().getBytes( "ISO8859-1" ) );
    }

    /**
     * <p>This method encodes the given Double value into
     * an RTS decimal field, and appends it to the end of the buffer.</p>
     * <p>If the Double value is null, the field will be encoded
     * as "null field". Typically this will result in the host
     * database storing a database null for this field.</p>
     * 
     * @param val
     */
    public final void appendField(Double val) throws UnsupportedEncodingException
    {

        if ( RTSTraceWriter._traceFileWriter != null )
           RTSTraceWriter._traceFileWriter.traceEncodeField( val );

        if ( val == null )
            appendUnknownField();
        else
            appendEncodedField( deciFmt.format(val).toString().getBytes( "ISO8859-1" ) );
    }


    /**
     * <p>This method encodes the given BigDecimal value into
     * an RTS decimal field, and appends it to the end of the buffer.</p>
     * <p>If the BigDecimal value is null, the field will be encoded
     * as "null field". Typically this will result in the host
     * database storing a database null for this field.</p>
     * 
     * @param val
     */
    public final void appendField(BigDecimal val) throws UnsupportedEncodingException
    {

        if ( RTSTraceWriter._traceFileWriter != null )
           RTSTraceWriter._traceFileWriter.traceEncodeField( val );

        if ( val == null )
            appendUnknownField();
        else
            appendEncodedField( quoteField(val.toString().getBytes(_encoding)) );
    }


    /**
     * <p>This method encodes the given Integer value into
     * and RTS integer field, and appends it to the end of the buffer.</p>
     * <p>If the Integer value is null, the field will be encoded
     * as "null field". Typically this will result in the host
     * database storing a database null for this field.</p>
     * 
     * @param val
     */
    public final void appendField(Integer val) throws UnsupportedEncodingException
    {
        
       if ( RTSTraceWriter._traceFileWriter != null )
           RTSTraceWriter._traceFileWriter.traceEncodeField( val );

       if ( val == null )
           appendUnknownField();
       else
           appendEncodedField( val.toString().getBytes( "ISO8859-1" ) );
    }

    /**
     * <p>This method encodes the given String value into
     * and RTS text field, and appends it to the end of the buffer.</p>
     * <p>If the String value is null, the field will be encoded
     * as "null field". Typically this will result in the host
     * database storing a database null for this field. This is
     * different from passing an empty string</p>
     * 
     * @param val
     */
    public final void appendField(String val) throws UnsupportedEncodingException
    {
        
        if ( RTSTraceWriter._traceFileWriter != null )
           RTSTraceWriter._traceFileWriter.traceEncodeField( val );

        if ( val == null )
            appendUnknownField();
        else
            appendEncodedField( quoteField( val.getBytes( _encoding ) ) );
    }

    /**
     *
     */
    private static byte[] quoteField( byte[] fieldBytes )
    {
        ByteArrayInputStream inFieldStream = new ByteArrayInputStream( fieldBytes );
        ByteArrayOutputStream outFieldStream = new ByteArrayOutputStream( 64 );

        int b;
        while ( ( b = inFieldStream.read() ) != -1 )
        {
//            if ( b=='\\' || b=='\n' )
//                outFieldStream.write( '\\' );

            outFieldStream.write(b);
        }

        return outFieldStream.toByteArray();

    }

    /**
     * Returns the underlying byte array. The RTSWriter class
     * uses this method as the source of data to be written to the stream.
     * 
     * @return buffers underlying byte array.
     */
    public byte[] toByteArray()
    {
       return _outByteStream.toByteArray();
    }

}

