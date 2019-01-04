#ifndef MESSAGEENCODING_H
#define MESSAGEENCODING_H


#include "Messaging.h"


namespace MessagingFramework
{

const std::string PAIR_DELIMITER      = ";";
const std::string KEY_VALUE_DELIMITER = "=";

const std::string ENCODED_PAIR_DELIMITER      = "%3B";   // HTTP URL Encoding
const std::string ENCODED_KEY_VALUE_DELIMITER = "%3D";   // HTTP URL Encoding



class KeyValuePairs;


/**
 * The MessageEncoding class is used to encode a KeyValuePairs object as
 * a string, and to decode ("un-encode") the string to a KeyValuePairs
 * object.  The default delimiters for the encoding and decoding are
 * meant to be used to encode/unencode IDI strings ("key1=value1;key2=value2").
 */
class DIMESSAGE_LINKAGE MessageEncoding
{
   public:


      /**
       * Encodes the contents of a KeyValuePairs object as a string (return
       * value).
       *
       * @param map - the KeyValuePairs object to encode
       * @param strPairDelimiter - the delimiter to use to separate key/value
       * pairs in the encoding
       * @param strKeyValueDelimiter - the delimiter to use to separate a key
       * from its value
       * @param strEncodedPairDelimiter - the encoded pair delimiter to use for embedded pair delimiters in application data
       * @param strEncodedKeyValueDelimiter - the encoded key/value delimiter to use for embedded key/value delimiters in application data
       *
       * @return the encoded string
       *
       * @see KeyValuePairs
       */
      static std::string encode( const KeyValuePairs& map,
                                 std::string strPairDelimiter=PAIR_DELIMITER,
                                 std::string strKeyValueDelimiter=KEY_VALUE_DELIMITER,
                                 std::string strEncodedPairDelimiter=ENCODED_PAIR_DELIMITER,
                                 std::string strEncodedKeyValueDelimiter=ENCODED_KEY_VALUE_DELIMITER );


      /**
       * Decodes ("un-encodes") an encoded string into a KeyValuePairs object.
       *
       * @param strData - the encoded string
       * @param mapData - the KeyValuePairs object to populate during the decoding
       * @param strPairDelimiter - the delimiter that was used to separate key/value
       * pairs during the encoding
       * @param strKeyValueDelimiter - the delimiter that was used to separate
       * a key from its value during the encoding
       * @param strEncodedPairDelimiter - the encoded pair delimiter to use for embedded pair delimiters in application data
       * @param strEncodedKeyValueDelimiter - the encoded key/value delimiter to use for embedded key/value delimiters in application data
       *
       * @see KeyValuePairs
       */
      static void decode( const std::string& strData,
                          KeyValuePairs& mapData,
                          std::string strPairDelimiter=PAIR_DELIMITER,
                          std::string strKeyValueDelimiter=KEY_VALUE_DELIMITER,
                          std::string strEncodedPairDelimiter=ENCODED_PAIR_DELIMITER,
                          std::string strEncodedKeyValueDelimiter=ENCODED_KEY_VALUE_DELIMITER );


      /**
       * Encodes a string by replacing all embedded key/value and pair delimiters with coded delimiters.
       *
       * @param str - the string to use for the encoding
       * @param strPairDelimiter - the delimiter used to separate key/value pairs
       * @param strKeyValueDelimiter - the delimiter used to separate a key from its value
       * @param strEncodedPairDelimiter - the encoded pair delimiter to use for embedded pair delimiters in application data
       * @param strEncodedKeyValueDelimiter - the encoded key/value delimiter to use for embedded key/value delimiters in application data
       *
       * @return the encoded string
       */
      static std::string encodeDelimiters( const std::string& str,
                                           const std::string& strPairDelimiter,
                                           const std::string& strKeyValueDelimiter,
                                           const std::string& strEncodedPairDelimiter,
                                           const std::string& strEncodedKeyValueDelimiter );


      /**
       * Decodes a string by replacing all embedded, encoded key/value and pair delimiters with decoded delimiters.
       *
       * @param str - the string to use for the decoding
       * @param strPairDelimiter - the delimiter to use to separate key/value pairs
       * @param strKeyValueDelimiter - the delimiter to use to separate a key from its value
       * @param strEncodedPairDelimiter - the encoded pair delimiter used for embedded pair delimiters in application data
       * @param strEncodedKeyValueDelimiter - the encoded key/value delimiter used for embedded key/value delimiters in application data
       *
       * @return the decoded string
       */
      static std::string decodeDelimiters( const std::string& str,
                                           const std::string& strPairDelimiter,
                                           const std::string& strKeyValueDelimiter,
                                           const std::string& strEncodedPairDelimiter,
                                           const std::string& strEncodedKeyValueDelimiter );


};

}

#endif


//************************************************************************
//              Revision Control Entries
//************************************************************************
//
// Name:
//    %PM%
//    %PID%
//
// Description:
//    %PD%
//
// Design Parts:
//    %PIRP%
//
// Last Changed:
//    %PO%  -  %PRT%
//
// Changes:
//    %PLA%
//
//



