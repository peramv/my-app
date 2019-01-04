package com.ifds.stubServer;

import java.io.*;
import java.util.*;
import java.text.ParseException;
import com.ifds.rts.*;


public class stubNameTable {
   private String stubInfoFileDir, stubInfoFilename;
   private static final String stubInfoFn = "stubInfo.cfg";
   String filename;
   private HashMap hm=null;
   
   class myDirFilter implements FilenameFilter {
      String ext;
      public myDirFilter(String ext) { this.ext = ext;}
      public boolean accept(File dir, String name) {
         
         String f = new File(name).getName();
         return f.indexOf(ext) != -1;
      }
   }
   
   
   public stubNameTable(String stubInfoFileDir) {
      this.stubInfoFileDir=stubInfoFileDir;
      stubInfoFilename=stubInfoFileDir+stubInfoFn;
      
      try {
         ObjectInputStream in =
         new ObjectInputStream( new FileInputStream(stubInfoFilename));
         hm=(HashMap)in.readObject();
      } catch (IOException e) {
         //System.out.println("io err");
      } catch (ClassNotFoundException ce) {
         //System.out.println("not found");
      }
      
      if (hm==null)hm = new HashMap();
   }
   
   public void finalize() {
      saveStubInfo();
   }
   
   public HashMap getStubInfoHashMap() {
      return hm;
   }
   
   private void saveStubInfo() {
      try {
         ObjectOutputStream out =
         new ObjectOutputStream( new FileOutputStream(stubInfoFilename));
         
         out.writeObject(hm);
      } catch (IOException e) {
      }
   }
   
   public synchronized String getOrAddStubFilename(String inputStr) {
      filename = (String)hm.get(inputStr);
      if ( filename==null ) {
         filename = (new Integer(hm.size()+1)).toString();
         hm.put(inputStr, filename);
         saveStubInfo();
      }
      
      return filename;
   }
   
   public String getStubFilename(String inputStr) {
      String orgInputStr = inputStr; 
      String name = (String)hm.get(inputStr);
      
      int pos ;
      Set hmKeySet;
      boolean isFinal = false;
      while( name == null && isFinal == false ){
         pos = inputStr.lastIndexOf(',');
         
         if( pos > 0 )
            inputStr = inputStr.substring(0, pos);
         else{
            isFinal = true;
            inputStr = inputStr.substring(0, 48);
         }
    
         hmKeySet = hm.keySet();
         
         Iterator iter = hmKeySet.iterator();
         String key;
         while (iter.hasNext()) {
            key = (String)iter.next();

            if( key.indexOf(inputStr) >= 0 ){
               System.out.println("Cannot find response for "+orgInputStr+".\nUse response for "+inputStr+" instead.");
               return (String)hm.get(key);
            }
         }
      }

      return (name == null || name.equals(""))? "0" : name;
   }
   
   public void displayStubInfo() {
      // load stub file info
      if ( hm!=null) {
         Set hmKeySet = hm.keySet();
         
         Iterator iter = hmKeySet.iterator();
         String key, value, str;
         while (iter.hasNext()) {
            key = (String)iter.next();
            value=(String)hm.get(key);
            
            str = value+".res\t\t"+key;
            
            System.out.println(str.substring(0, Math.min(80,str.length())));
         }
         
      }
   }
   
   public void clearStubInfo() {
      hm.clear();
   }
   
   public void recreateStubInfo() {
      hm.clear();
      mergeStubInfo();
   }
   
   public void mergeStubInfo() {
      File path = new File(stubInfoFileDir);
      String[] list;
      RTSReader fileReader = null;
      int index;
      list = path.list(new myDirFilter(".req"));
      for (int i = 0; i < list.length; i++) {
         try {
            fileReader = new RTSReader( new FileInputStream(stubInfoFileDir+list[i]) );
         } catch (FileNotFoundException e) {
            System.out.println("Error: file "+list[i]+" is not found.");
            continue;
         }
         
         RTSResponseDecodeBuffer responseBuffer = null;
         try {
            responseBuffer = fileReader.readResponse( "ISO8859-1" );
         } 
         catch (IOException ioe) {
            System.out.println("Error: file "+list[i]+" contains wrong data.");
            continue;
         }
         catch (ParseException ioe) {
            System.out.println("Error: file "+list[i]+" contains wrong data.");
            continue;
         }
         
         index = list[i].indexOf(".req");
         
         list[i]=list[i].substring(0,index);
         
         hm.put(responseBuffer.toString(), list[i]);
         
         System.out.println(list[i] +"\t\tis added to the stu4b info file.");
      }
      
      saveStubInfo();
   }
}
