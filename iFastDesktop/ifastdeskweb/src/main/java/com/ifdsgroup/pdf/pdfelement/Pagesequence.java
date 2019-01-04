package com.ifdsgroup.pdf.pdfelement;

/*
 * @author Zijian Ying
 */

public class Pagesequence extends PDFElement {
   private Simplepagemaster pagemaster = null;

   public void doStart() throws Exception {
      pagemaster = getPdfDoc().getLayoutmasterset().getSimplepagemaster(
            getString("master-reference"));
      getPdfDoc().setCurrentPagemaster(pagemaster);

      //pl.begin_page( (double)pagemaster.getPagewidth(), (double)pagemaster.getPageheight());
      pl.begin_page( pagemaster.getPagewidth(), pagemaster.getPageheight());
   }

   public void doEnd(String text) throws Exception {
      pl.end_page();
   }
}
