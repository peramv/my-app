/*********************************************************************************************
 * @file	DesktopWeb.Main.js
 * @author	Rod Walker 
 * @desc	Main javascript file for DesktopWeb screen, builds wrapper then 
 * 			initializes and loads screen specific code
 *********************************************************************************************/
/*
 *  History : 
 *
 *  01 Nov 2013 G. Thawornwachirakun P0181067 CHG0034430 T54333
 *					- Add useStrict to not autorotate date in dateField.
 */
 
// required by ExtJS library for screen to render correctly
Ext.BLANK_IMAGE_URL = DesktopWeb._SRC_PATH + 'extjs/resources/images/gray/s.gif';
Date.useStrict = true;
Ext.onReady(function(){
	Ext.QuickTips.init();
	
	// Build screen controller object	
	DesktopWeb._SCREEN_CONTROLLER = new DesktopWeb.ScreenController();	
	// Build screen resources object
	DesktopWeb._SCREEN_RESOURCES = new DesktopWeb.ScreenResources(DesktopWeb._SCREEN_CONTROLLER);
	
	// Build and render screen wrapper container, adding buttons and content from resources
	var wrapper = new Ext.Container(
		{						
			layout: 'fit'
			,width: DesktopWeb.Util.calcScreenWidth()
			,height: DesktopWeb.Util.calcScreenHeight()
			,items: [
				new Ext.form.FormPanel(
					{					  
						border: true
						,footerCfg: {
							cls: 'DesktopWebFooter'
						}
						,frame: true						
						,items: DesktopWeb._SCREEN_RESOURCES.layout
						,buttons: DesktopWeb._SCREEN_RESOURCES.screenButtons
					}
				)
			]
		}
	);
	wrapper.render(document.body);
			
	// Initialize screen - i.e. run init view, load defaults, etc.	
	DesktopWeb._SCREEN_CONTROLLER.init(DesktopWeb._SCREEN_RESOURCES);		
});