FormToolbar = Ext.extend(Ext.Panel, {	
	initComponent: function(){
		var toolbar = new Ext.Toolbar();
		
		this.smfButtons = {};
		
		this.smfButtons['lookup'] = new FormToolbarButton({
			iconCls: 'lookupBtn'
			,enableToggle: true					
			,tooltip: "iFAST account lookup"
			,disabled: false					
		});		
		toolbar.add(this.smfButtons['lookup']);
				
		if (this.initialConfig.showAWDTools)
		{
			toolbar.add(new Ext.Toolbar.Separator());
						
			this.smfButtons['move'] = new FormToolbarButton({
				iconCls: 'moveBtn'
				,enableToggle: true		
				,tooltip: "Re-position source page"		
				,toggleHandler: function(button, state){
					if (state)
					{
						SmartFormsApp.ContentViewer.enableSourceDrag();
						SmartFormsApp.PageNavigator.disablePageSelection();
					}
					else
					{
						SmartFormsApp.ContentViewer.disableSourceDrag();
						SmartFormsApp.PageNavigator.enablePageSelection();
					}
				}			
			});		
			toolbar.add(this.smfButtons['move']);
												
			this.smfButtons['stretch'] = new FormToolbarButton({
				iconCls: 'stretchBtn'
				,tooltip: "Stretch source page"
				,handler: function(){
					SmartFormsApp.ContentViewer.resizeSourceImage(0.02);
				}
			});		
			toolbar.add(this.smfButtons['stretch']);
			
			this.smfButtons['shrink'] = new FormToolbarButton({
				iconCls: 'shrinkBtn'
				,tooltip: "Shrink source page"
				,handler: function(){
					SmartFormsApp.ContentViewer.resizeSourceImage(-0.02);					
				}
			});		
			toolbar.add(this.smfButtons['shrink']);					
			
			this.smfButtons['nudgeCW'] = new FormToolbarButton({
				iconCls: 'nudgeCWBtn'
				,tooltip: "De-skew source page (clockwise)"
				,handler: function(){
					SmartFormsApp.ContentViewer.rotateSourceImage(1, 1);					
				}
			});		
			toolbar.add(this.smfButtons['nudgeCW']);
			
			this.smfButtons['nudgeCCW'] = new FormToolbarButton({
				iconCls: 'nudgeCCWBtn'
				,tooltip: "De-skew source page (counter-clockwise)"
				,handler: function(){
					SmartFormsApp.ContentViewer.rotateSourceImage(0, 1);
				}
			});		
			toolbar.add(this.smfButtons['nudgeCCW']);
			
			this.smfButtons['rotateCW'] = new FormToolbarButton({
				iconCls: 'rotateCWBtn'
				,tooltip: "Rotate source page (clockwise)"
				,handler: function(){
					SmartFormsApp.ContentViewer.rotateSourceImage(1, 90);
				}
			});		
			toolbar.add(this.smfButtons['rotateCW']);
			
			this.smfButtons['rotateCCW'] = new FormToolbarButton({
				iconCls: 'rotateCCWBtn'
				,tooltip: "Rotate source page (counter-clockwise)"
				,handler: function(){
					SmartFormsApp.ContentViewer.rotateSourceImage(0, 90);
				}
			});		
			toolbar.add(this.smfButtons['rotateCCW']);
			
			toolbar.add(new Ext.Toolbar.Separator());
			
			this.smfButtons['sections'] = new FormToolbarButton({
				iconCls: 'sectionsBtn'
				,tooltip: "Toggle source bubble sections"
				,enableToggle: true
				,toggleHandler: function(button, state)
				{
					if (state)
					{
						SmartFormsApp.ContentViewer.sourceBubble.enableSections();
					}
					else
					{					
						SmartFormsApp.ContentViewer.sourceBubble.disableSections();
					}
				}
			});		
			toolbar.add(this.smfButtons['sections']);		
		}		
		
		var config = {					
			id: 'FormToolbar'		
			,height:29
			,border: false							
			,tbar: toolbar		
		};
		
		Ext.apply(this, Ext.apply(this.initialConfig, config));	
		FormToolbar.superclass.initComponent.apply(this, arguments);
	}
	
	,onRender: function(ct, position)
	{
		FormToolbar.superclass.onRender.call(this, ct, position);		
	}
	
	,enableFormTools: function()
	{
		if (this.smfButtons['sections'])
		{
			this.smfButtons['sections'].enable();
		}
	}
	
	,disableFormTools: function()
	{
		if (this.smfButtons['sections'])
		{
			this.smfButtons['sections'].disable();
		}
	}
	
	,enableSourceTools: function()
	{		
		this.smfButtons['move'].enable();
		this.smfButtons['stretch'].enable();
		this.smfButtons['shrink'].enable();
		this.smfButtons['nudgeCW'].enable();
		this.smfButtons['nudgeCCW'].enable();		
		this.smfButtons['rotateCW'].enable();
		this.smfButtons['rotateCCW'].enable();		
	}
	
	,disableSourceTools: function()
	{		
		this.smfButtons['move'].disable();
		this.smfButtons['stretch'].disable();
		this.smfButtons['shrink'].disable();
		this.smfButtons['nudgeCW'].disable();
		this.smfButtons['nudgeCCW'].disable();		
		this.smfButtons['rotateCW'].disable();
		this.smfButtons['rotateCCW'].disable();		
	}
});

FormToolbarButton = Ext.extend(Ext.Button, {
	tooltip: 'no tooltip yet ...'
	,disabled: true	
	
	,initComponent: function(){
		
		var config = {			
			width: 30
			,disabledClass: 'disabled_button'					
		}		
		
		Ext.apply(this, Ext.apply(this.initialConfig, config));	
		FormToolbarButton.superclass.initComponent.apply(this, arguments);
	}
	
	,onRender: function(ct, position)
	{
		FormToolbarButton.superclass.onRender.call(this, ct, position);
	}
});

