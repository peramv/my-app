Footer = Ext.extend(Ext.Panel, {
	
	initComponent: function()
	{
		this.appButtons = {};		
		this.appButtons['submit'] = new DesktopWeb.Controls.ScreenButton(
			{
				text: 'Submit'
				,tabIndex: 32001
				,hidden: true										
				,iconCls: 'submit'
				,style: "position:absolute; right:100px; top: 4px;"																
			}
		);
		this.appButtons['submit'].setHandler(this.submitHandler);
		
		this.appButtons['cancel'] = new DesktopWeb.Controls.ScreenButton(
			{
				text: 'Cancel'
				,hidden: true
				,handler: function(){DesktopWeb.Util.cancelScreen();}
				,style: "position:absolute; right:10px; top: 4px;"
				,iconCls: 'cancel'						
			}
		);
		
		this.appButtons['resubmit'] = new DesktopWeb.Controls.ScreenButton(
			{
				text: 'Re-Submit'				
				,hidden: true
				,style: "position:absolute; right:100px; top: 4px;"
				,iconCls: 'resubmit'
			}
		);
		
		this.appButtons['done'] = new DesktopWeb.Controls.ScreenButton(
			{
				text: 'Done'
				,handler: function(){
					SmartFormsApp.done();
					}
				,hidden: true
				,style: "position:absolute; right:10px; top: 4px;"
				,iconCls: 'done'						
			}
		)		
					
		var config = {
			region: 'south'
			,height: 35						
			,split: false
			,items: [
				this.appButtons['submit'], this.appButtons['cancel'], this.appButtons['resubmit'], this.appButtons['done']				
			]
		};
		
		Ext.apply(this, Ext.apply(this.initialConfig, config));	
		Footer.superclass.initComponent.apply(this, arguments);
		
		this.setMode('submit');		
	}
	
	,setMode: function(mode)
	{
		if (mode == 'submit')
		{
			this.appButtons['submit'].show();
			this.appButtons['cancel'].show();
			this.appButtons['resubmit'].hide();
			this.appButtons['done'].hide();			
		}
		else if (mode == 'resubmit_cancel')
		{		
			this.appButtons['submit'].hide();
			this.appButtons['cancel'].show();
			this.appButtons['resubmit'].show();
			this.appButtons['resubmit'].setHandler(this.submitHandler);
			this.appButtons['done'].hide();
		}
		else
		{
			this.appButtons['submit'].hide();
			this.appButtons['cancel'].hide();
			this.appButtons['resubmit'].show();
			this.appButtons['resubmit'].setHandler(this.resubmitHandler);
			this.appButtons['done'].show();
		}
	}
	
	,submitHandler: function()
	{
		if (SmartFormsApp.validate())
		{
			SmartFormsApp.submit();
		}
	} 		
	
	,resubmitHandler: function()
	{
		if (SmartFormsApp.validate())
		{
			SmartFormsApp.resubmit();
		}
	} 											
});