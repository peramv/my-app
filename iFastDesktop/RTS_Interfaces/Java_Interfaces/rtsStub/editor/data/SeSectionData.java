package com.ifds.stubEditor.data;

import com.ifds.rts.*;
import java.text.ParseException;
import java.io.UnsupportedEncodingException;

public interface SeSectionData
{
   public void initFromBuffer( RTSDecodeBuffer buffer ) throws ParseException, UnsupportedEncodingException;
   public void saveToBuffer( RTSEncodeBuffer buffer ) throws ParseException, UnsupportedEncodingException;
   public boolean isDirty();
   public boolean isRepeatSection();
}
