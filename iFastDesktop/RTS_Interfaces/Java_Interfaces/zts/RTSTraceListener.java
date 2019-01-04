package com.ifds.rts;

import java.util.*;
import java.text.*;
import java.math.*;

public interface RTSTraceListener
{
   public void traceResponseBuffer( String responseBuffer );

   public void traceDecodeHeader( String  msgType,
                           Integer transactionID,
                           Integer responseID,
                           Integer responseType,
                           Integer pHandleID,
                           Long    pThreadID,
                           Integer instanceID );

   public void traceDecodeField( Boolean field );
   public void traceDecodeField( Date field    );
   public void traceDecodeField( Double field  );
   public void traceDecodeField( BigDecimal field  );
   public void traceDecodeField( Integer field );
   public void traceDecodeField( String field  );

   public void traceTransactionBuffer( String transactionBuffer );

   public void traceAppendField( Boolean field );
   public void traceAppendField( Date field    );
   public void traceAppendField( Double field  );
   public void traceAppendField( BigDecimal field  );
   public void traceAppendField( Integer field );
   public void traceAppendField( String field  );
}
