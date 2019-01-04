package com.ifds.rts;

import java.text.SimpleDateFormat;
import java.text.ParseException;
import java.util.Date;
import java.io.*;
import java.math.*;

/**
 * <p>RTSDecodeBuffer provides an abstract base class for 
 * all decodable RTS buffers. It provides the base class
 * for RTSRequestDecodeBuffer and RTSResponseDecodeBuffer,
 * providing common methods for decoding header and 
 * non-header fields.</p>
 * <p>All constructors are of package scope so that 
 * other packages cannot add specializations.</p>
 */
public class RTSDecodeBuffer implements RTSBuffer
{
    /**
	 * 
	 */
	private static final long serialVersionUID = 1L;

	private final SimpleDateFormat dateFmt = new SimpleDateFormat("MMddyyyy");   //Simple date format cannot be made static

    private String _encoding;
    private byte[] _inBytes;
    private ByteArrayInputStream _inByteStream;

    private int _byteCount;
    private int _fieldCount;
    
//    private String separator = System.getProperty("SEPARATOR")!=null? System.getProperty("SEPARATOR") : ",";
    private String separator = "\u00fe";
//    private String separator = "þ";

    //To store fields as they extracted in 'getNextField()' and re-used everytime
    private ByteArrayOutputStream fieldByteStream = new ByteArrayOutputStream( 64 );

    RTSDecodeBuffer( byte[] bytes, String encoding )
    {
        _encoding = encoding;
        _inBytes = bytes;
        _inByteStream = new ByteArrayInputStream( bytes );

        _byteCount=0;
        _fieldCount=0;
        
        if ( RTSTraceWriter._traceFileWriter != null )
           RTSTraceWriter._traceFileWriter.traceDecodeBufferCreated();

    }

    protected final String decodeHeaderField( int length ) throws ParseException, UnsupportedEncodingException
    {
        byte[] headerBytes = new byte[length];

        int bytesRead = _inByteStream.read( headerBytes, 0, length );
        _byteCount += bytesRead;

        if ( bytesRead < length )
            throw new ParseException( "Unexpectecd end of record found decoding header.", bytesRead);


        return new String( headerBytes, "ISO8859-1" );
    }


    /**
     * <p>This method decodes the passed "RTS field" encoded
     * as a Boolean.</p>
     * <p>RTS fields may have no value, which typically
     * indicates the host database field has a "null" entry.
     * In this case this method returns null.</p>
     * 
     * @param fieldBytes      RTS encoded logical field
     * @return Boolean object decoded from the given field string, or null.
     * @exception ParseException
     *                   A Boolean value could not be decoded from the given field string.
     */
    public final Boolean decodeBoolean( byte[] fieldBytes ) throws ParseException, UnsupportedEncodingException
    {

        Boolean val = null;

        if ( fieldBytes != null )
        {

            String fieldValue = new String( fieldBytes, "ISO8859-1" );

            if ( fieldValue.equals("Y") )
                return Boolean.TRUE;
            else if ( fieldValue.equals("N") )
                return  Boolean.FALSE;
            else
                throw new ParseException( "Invalid boolean value [" + fieldValue + "]", (_byteCount - 1) ); 

        }

        if ( RTSTraceWriter._traceFileWriter != null )
           RTSTraceWriter._traceFileWriter.traceDecodeField( val );

        return val;
    }


    /**
     * <p>This method decodes the passed "RTS field" encoded
     * as a Date.</p>
     * <p>RTS fields may have no value, which typically
     * indicates the host database field has a "null" entry.
     * In this case this method returns null.</p>
     * 
     * @param fieldBytes      RTS encoded date field
     * @return Date object decoded from the given field string, or null.
     * @exception ParseException
     *                   A Date value could not be decoded from the given field string.
     */
    public final Date decodeDate( byte[] fieldBytes ) throws ParseException, UnsupportedEncodingException
    {

        Date val = (fieldBytes==null)?null:dateFmt.parse( new String( fieldBytes, "ISO8859-1" ) );

        if ( RTSTraceWriter._traceFileWriter != null )
           RTSTraceWriter._traceFileWriter.traceDecodeField( val );

        return val;
    }

    /**
     * <p>This method decodes the passed "RTS field" encoded
     * as a Double.</p>
     * <p>RTS fields may have no value, which typically
     * indicates the host database field has a "null" entry.
     * In this case this method returns null.</p>
     * 
     * @param fieldBytes      RTS encoded decimal field
     * @return Double object decoded from the given field string, or null.
     * @exception ParseException
     *                   A Double value could not be decoded from the given field string.
     */
    public final Double decodeDouble( byte[] fieldBytes ) throws ParseException, UnsupportedEncodingException
    {
        try
        {
            Double val = (fieldBytes==null)?null:new Double( new String( fieldBytes, "ISO8859-1" ) );
            
            if ( RTSTraceWriter._traceFileWriter != null )
               RTSTraceWriter._traceFileWriter.traceDecodeField( val );

            return val;
        }
        catch ( NumberFormatException nfe )
        {
            throw new ParseException("Unable to parse Double : " + nfe.getMessage(), (_byteCount - 1));

        }

    }

    /**
     * <p>This method decodes the passed "RTS field" encoded
     * as a BigDecimal.</p>
     * <p>RTS fields may have no value, which typically
     * indicates the host database field has a "null" entry.
     * In this case this method returns null.</p>
     * 
     * @param fieldBytes      RTS encoded BigDecimal field
     * @return BigDecimal object decoded from the given field string, or null.
     * @exception ParseException
     *                   A BigDecimal value could not be decoded from the given field string.
     */
    public final BigDecimal decodeBigDecimal( byte[] fieldBytes ) throws ParseException, UnsupportedEncodingException
    {
        try
        {
            BigDecimal val = (fieldBytes==null)?null:new BigDecimal( new String( fieldBytes, _encoding) );

            if ( RTSTraceWriter._traceFileWriter != null )
               RTSTraceWriter._traceFileWriter.traceDecodeField( val );

            return val;
        }
        catch ( NumberFormatException nfe )
        {
            throw new ParseException("Unable to parse BigDecimal : " + nfe.getMessage(), (_byteCount - 1));
        }
    }

    /**
     * <p>This method decodes the passed "RTS field" encoded
     * as a Integer.</p>
     * <p>RTS fields may have no value, which typically
     * indicates the host database field has a "null" entry.
     * In this case this method returns null.</p>
     * 
     * @param fieldBytes      RTS encoded integer field
     * @return Integer object decoded from the given field string, or null.
     * @exception ParseException
     *                   An Integer value could not be decoded from the given field string.
     */
    public final Integer decodeInteger( byte[] fieldBytes ) throws ParseException, UnsupportedEncodingException
    {
        try
        {
            Integer val = (fieldBytes==null)?null:new Integer( new String( fieldBytes, "ISO8859-1" ) );

            if ( RTSTraceWriter._traceFileWriter != null )
               RTSTraceWriter._traceFileWriter.traceDecodeField( val );

            return val;
        }
        catch ( NumberFormatException nfe )
        {
            throw new ParseException("Unable to parse Integer : " + nfe.getMessage(), (_byteCount - 1));
        }
    }

    /**
     * <p>This method decodes the passed "RTS field" encoded
     * as a String.</p>
     * <p>RTS fields may have no value, which typically
     * indicates the host database field has a "null" entry.
     * In this case this method returns null. This is different
     * than a text field that is empty, which results in an empty
     * string.</p>
     * 
     * @param fieldBytes      RTS encoded text field
     * @return String object decoded from the given field string, or null.
     * @exception ParseException
     *                   A String value could not be decoded from the given field string.
     */
    public final String decodeString( byte[] fieldBytes ) throws ParseException, UnsupportedEncodingException
    {
        String val = (fieldBytes==null)?null:new String( fieldBytes, _encoding );

        if ( RTSTraceWriter._traceFileWriter != null )
           RTSTraceWriter._traceFileWriter.traceDecodeField( val );

        return val;
    }

    /**
     * <p>This method traverses the underlying buffer 
     * from the current buffer position to the end of
     * the next field. The un-decoded RTS field is
     * return. This is typially passed to one of the
     * decode methods for decoding as follows:</p>
     * <code>
     * Boolean isPreferredClient = decodeBoolean( getNextField() );<br>
     * String  clientSurname = decodeString( getNextField() );<br>
     * Boolean clientGivenName = decodeString( getNextField() );<br>
     * </code>
     * 
     * @return "RTS field" encoded string.
     * @exception ParseException
     *                   indicates that a field could not be parsed from the underlying buffer,
     *                   possibly at the end of the buffer.
     */
    public final byte[] getNextField() throws ParseException
    {

        switch ( _inByteStream.read() )
        {
        case 'F':
            _byteCount++;
            break;
        case 'T':
            _byteCount++;
            int b = _inByteStream.read();
            _byteCount++;
            if ( b != -1 && b != separator.charAt(0) )
                throw new ParseException( "RTSDecodeBuffer.getNextField() found field data for null field.[Field #" + (_fieldCount + 1) + "]", _byteCount );
            _fieldCount++;
            return null;
        case -1:
            throw new ParseException( "RTSDecodeBuffer.getNextField() attempted to get more fields than there are in the response buffer.[Field #" + (_fieldCount + 1) + "]", _byteCount );
        default:
            throw new ParseException( "RTSDecodeBuffer.getNextField() could not parse field prefix.[Field #" + (_fieldCount + 1) + "]", _byteCount );
        }

        //***ByteArrayOutputStream fieldByteStream = new ByteArrayOutputStream( 64 );**** NOT NEEDED ANYMORE
        //This ByteArrayOutputStream will be instantiated once for each RTSDecodeBuffer and re-used
        //so reset buffer content each time, as below
        fieldByteStream.reset();

        boolean escaped = false;
        int b;

        while ( ( b = _inByteStream.read() ) != -1 )
        {
            _byteCount++;

            if ( escaped == false )
            {
/*
                if ( b == '\\' )
                {
                    escaped = true;
                    continue;
                }
*/		
                if ( b == separator.charAt(0) ) break;
            }
	    
            fieldByteStream.write( b );
            escaped = false;
        }

        _fieldCount++;
        return fieldByteStream.toByteArray();
    }

    /**
     * Returns the underlying byte array. The RTSWriter class
     * uses this method as the source of data to be written to the stream.
     * 
     * @return buffers underlying byte array.
     */
    public byte[] toByteArray()
    {
        return _inBytes;
    }

}
