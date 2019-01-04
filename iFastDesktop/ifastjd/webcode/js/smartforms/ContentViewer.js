ContentViewer = Ext.extend(Ext.Container, {
	initComponent: function()
	{
		var config = {
			id: 'ContentViewer'
			,region: 'center'
			,border: false
			,autoScroll: true
		}; 
				
		Ext.apply(this, Ext.apply(this.initialConfig, config));	
		ContentViewer.superclass.initComponent.apply(this, arguments);			
		
		this.formPageContainer = null;
		this.sourceBubble = null;
		
		this.sourcePageContainer = null;
		this.formBubble = null;
		
		if (this.initialConfig.source)
		{
			this.sourceBubble = new SourceBubble({
				images: this.initialConfig.source.images, 
				formLayout: this.initialConfig.formLayout
			});				
			this.sourcePageContainer = new SourcePageContainer({
				images: this.initialConfig.source.images
				,formLayout: this.initialConfig.formLayout
				,bubble: null
			});
			this.add(this.sourcePageContainer);
		}
		
		if (this.initialConfig.form)
		{
			this.formPageContainer = new FormPageContainer({
				images: this.initialConfig.form.images 
				,formLayout: this.initialConfig.formLayout 
				,bubble: this.sourceBubble
			});
					
			this.add(this.formPageContainer);
		}
		
		this.addListener('afterrender', this.onAfterRender, this);		
	}
	
	,onAfterRender: function()
	{
		if (this.sourceBubble)
		{
			this.sourceBubble.render(this.el);
		}
	}
	
	,showPage: function(pageType, index)
	{				
		if (pageType == 'form')
		{	
			var correspondingSourcePageIndex = null;				
			if (this.sourcePageContainer)
			{
				if(this.sourceBubble.isVisible())
				{
					this.sourceBubble.hide();
					this.sourcePageContainer.hide();
				}
				else
				{
					this.sourcePageContainer.hide()
				};
				SmartFormsApp.Toolbar.disableSourceTools();				
				correspondingSourcePageIndex = this.sourcePageContainer.getCorrespondingPageIndex(index);						
			}
			
			if (this.formPageContainer)
			{							
				this.formPageContainer.show();				
				this.formPageContainer.showPage(index, correspondingSourcePageIndex);
				SmartFormsApp.Toolbar.enableFormTools();				
			}
		}
		else
		{
			if (this.formPageContainer)
			{
				this.formPageContainer.hide();
				SmartFormsApp.Toolbar.disableFormTools();
			}			
			if (this.sourcePageContainer)
			{
				this.sourcePageContainer.show();						
				this.sourcePageContainer.showPage(index);
				this.sourcePageContainer.focus();
				SmartFormsApp.Toolbar.enableSourceTools();
			}
		}		
	}
	
	,focus: function()
	{		
		if (this.formPageContainer.isVisible())
		{
			this.formPageContainer.prevPageBtn.focus();
		}
		else
		{
			this.sourcePageContainer.prevPageBtn.focus();
		}
	}
	
	,scrollTo: function(top)
	{
		this.el.dom.scrollTop = top;
	}
	
	,disableControlsForAPI: function(apiName, index)
	{
		if (this.formPageContainer)
		{
			this.formPageContainer.disableControlsForAPI(apiName, index)
		}
	}
	
	,getFormPageCount: function()
	{
		if (this.formPageContainer)
		{
			return this.formPageContainer.pages.length;
		}
		return null;
	}
	
	,getSourcePageCount: function()
	{
		if (this.sourcePageContainer)
		{
			return this.sourcePageContainer.pages.length;
		}
		return null;
	}
	
	,rotateSourceImage: function(direction, degreeVal)
	{		
		this.sourcePageContainer.rotateImage(direction, degreeVal);
		this.sourceBubble.sourcePageContainer.rotateImage(direction, degreeVal);		
	}
	
	,resizeSourceImage: function(val)
	{		
		this.sourcePageContainer.resizeImage(val);
		this.sourceBubble.sourcePageContainer.resizeImage(val);		
	}
	
	,enableSourceDrag: function()
	{
		this.sourcePageContainer.enableImageDrag();
	}
	
	,disableSourceDrag: function()
	{
		this.sourcePageContainer.disableImageDrag();
		
		var page = this.sourcePageContainer.pages[this.sourcePageContainer.currentPageIndex];
		this.sourceBubble.setBackgroundPosition(this.sourcePageContainer.currentPageIndex,
		 	page.background.el.dom.style.top, page.background.el.dom.style.left);		
	}
	
	,disableSourcePage: function(index)
	{
		this.sourcePageContainer.disablePage(index);
		this.sourceBubble.disablePage(index);
	}
	
	,enableSourcePage: function(index)
	{
		this.sourcePageContainer.enablePage(index);
		this.sourceBubble.enablePage(index);
	}
});

PageContainer = Ext.extend(Ext.Container, {
	
	initComponent: function()
	{	
		this.pages = [];
		
		this.prevPageBtn = new DesktopWeb.Controls.ActionButton({
			text: 'Previous Page'
			,width: 120
			,tabIndex: 1000	
			,iconCls: 'leftArrow'
			,iconAlign: 'left'							
		})
		
		this.nextPageBtn = new DesktopWeb.Controls.ActionButton({
			text: 'Next Page'
			,width: 120
			,tabIndex: 32000 //assume never be any 32 page forms		
			,iconCls: 'rightArrow'
			,iconAlign: 'right'			
		}) 		
	
		var config = {			
			layout: 'absolute'
			,cls: 'PageContainer'
			,height: 1000
			,width: 900
			,hidden: true
			,items: [this.prevPageBtn, this.nextPageBtn]												
		};
		
		Ext.apply(this, Ext.apply(this.initialConfig, config));	
		PageContainer.superclass.initComponent.apply(this, arguments);
		
		this.currentPageIndex = null;		
	}
		
	,hideAllPages: function()
	{
		Ext.each(this.pages, function(item){item.hide()});
	}
	
	,showPage: function(index)
	{		
		this.hideAllPages();
				
		this.setHeight(this.pages[0].getHeight() + 3 /*for border width*/);
		this.setWidth(this.pages[0].getWidth() + 3 /*for border width*/);
				
		this.currentPageIndex = index;
		
		this.updatePageButtons();
		this.pages[index].show();
	}
	
	,updatePageButtons: function()
	{
		this.prevPageBtn.setPosition((this.getWidth() - this.prevPageBtn.getWidth())/2, -28);
				
		this.nextPageBtn.setPosition((this.getWidth() - this.nextPageBtn.getWidth())/2, this.getHeight() + 4);
		
		if (this.currentPageIndex == 0)
		{
			this.prevPageBtn.disable();			
		}
		else
		{
			this.prevPageBtn.enable();
		}
		
		if (this.currentPageIndex == this.pages.length - 1)
		{		
			this.nextPageBtn.disable();
		}
		else
		{		
			this.nextPageBtn.enable();
		}		
	}
});

FormPageContainer = Ext.extend(PageContainer, {
	initComponent: function(){
		FormPageContainer.superclass.initComponent.apply(this, arguments);
				
		for (var p = 0; p < this.initialConfig.images.length; p++)
		{		
			this.pages[p] = new Page({
				image: this.initialConfig.images[p]
				,pageType: 'form'
				,index: p
			});
			this.pages[p].addClass('FormPage')
			this.add(this.pages[p]);
		}
		
		this.sourceBubble = this.initialConfig.bubble;
		this.sourcePageIndex = null;	
						
		if (this.initialConfig.formLayout)
		{						
			var formLayout = this.initialConfig.formLayout;
			for (var p = 0; p < formLayout.pages.length; p++)
			{	
				for (var s = 0; s < formLayout.pages[p].sections.length; s++)
				{		
					var section = new FormItems.Section({
						y: formLayout.pages[p].sections[s].top
						,height: formLayout.pages[p].sections[s].height
					});
					
					for (var c = 0; c < formLayout.pages[p].sections[s].controls.length; c++)
					{
						var control = FormPageContainer.buildControl(formLayout.pages[p].sections[s].controls[c]);
						if (control != null)
						{
							control.addListener('focus', this.onControlFocus, this);
							section.add(control);
						}
					}									
					this.pages[p].addToContents(section);				
				}				
			}
		}
		
		this.prevPageBtn.addListener('click', function(){
			SmartFormsApp.PageNavigator.setSelectedPage('form', this.currentPageIndex - 1);
			}, this);
			
		this.nextPageBtn.addListener('click', function(){
			SmartFormsApp.PageNavigator.setSelectedPage('form', this.currentPageIndex + 1);
			}, this);
			
		this.addListener('hide', this.hideHandler, this);		
	}
	
	,onControlFocus: function(control)
	{
		if (this.sourceBubble && this.sourcePageIndex != null)
		{
			if (!this.sourceBubble.isVisible())
			{
				this.sourceBubble.show();
				control.focus(false, 10);   // bug in ExtJS - opening a window steals focus
			}
			this.sourceBubble.setDisplay(this.sourcePageIndex, control);
		}
	}
	
	,hideHandler: function()
	{
		if (this.sourceBubble)
		{
			this.sourceBubble.hide();
		}
	}
	
	,showPage: function(index, sourcePageIndex)
	{
		FormPageContainer.superclass.showPage.call(this, index);
		this.sourcePageIndex = sourcePageIndex;
		
		var control = this.pages[index].focus();
		if (control == null)
		{			
			SmartFormsApp.ContentViewer.focus();
			SmartFormsApp.ContentViewer.scrollTo(0);
		}
		else
		{
			SmartFormsApp.ContentViewer.scrollTo(control.getPagePosition()[1] - 100);	
		}						
	}
	
	,disableControlsForAPI: function(apiName, index)
	{
		var nodes = SmartFormsApp.DataStore.getRootNode().childNodes;		
		var rootNodeForAPI = null;
		for (var i = 0; i < nodes.length; i++)
		{
			if (nodes[i].name == apiName + "Request" && nodes[i].hasData())
			{											
				if (index == 0 || index == null)
				{
					rootNodeForAPI = nodes[i];
					break;
				}
				else
				{
					index--;
				}		
			}
		}
					
		var controls = this.findBy(function(item, container){			
			
			if ((item.dataStoreNode 
				&& item.dataStoreNode.isAncestor && item.dataStoreNode.isAncestor(rootNodeForAPI)))
			{								
				item.disableField();
				return true;
			}			
			return false;
		})			
	}
});

FormPageContainer.buildControl = function(smartformControlProps)
{
	var control = null;
	
	if (smartformControlProps.controlType == 'verify'
		|| smartformControlProps.controlType == 'indicator'
		|| SmartFormsApp.DataStore.isAPIAvailable(smartformControlProps.dataMapping))	
	{	
		switch (smartformControlProps.controlType)
		{		
			case 'text': {
				var missingProps = FormItems.Util.checkRequiredProperties(smartformControlProps, FormItems.TextField.SmartFormProperties);
				if (missingProps.length == 0)
				{ 			
					control = new FormItems.TextField(smartformControlProps)
				}
				else
				{
					throw new Error("Could not build text form control ('" + smartformControlProps.description + "') - missing " + missingProps);
				}			
				break;
			}
			case 'hidden': {
				var missingProps = FormItems.Util.checkRequiredProperties(smartformControlProps, FormItems.HiddenField.SmartFormProperties);
				if (missingProps.length == 0)
				{ 			
					control = new FormItems.HiddenField(smartformControlProps);
				}
				else
				{
					throw new Error("Could not build hidden form control ('" + smartformControlProps.description + "') - missing " + missingProps);
				}							
				break;
			}
			case 'combobox': {
				var missingProps = FormItems.Util.checkRequiredProperties(smartformControlProps, FormItems.APIComboBox.SmartFormProperties);
				if (missingProps.length == 0)
				{ 			
					control = new FormItems.APIComboBox(smartformControlProps);
				}
				else
				{
					throw new Error("Could not build combobox form control ('" + smartformControlProps.description + "') - missing " + missingProps);
				}																										
				break;
			}	
			case 'date': {
				var missingProps = FormItems.Util.checkRequiredProperties(smartformControlProps, FormItems.DateField.SmartFormProperties);
				if (missingProps.length == 0)
				{ 			
					control = new FormItems.DateField(smartformControlProps);
				}
				else
				{
					throw new Error("Could not build date form control ('" + smartformControlProps.description + "') - missing " + missingProps);
				}								
				break;
			}
			case 'checkbox': {
				var missingProps = FormItems.Util.checkRequiredProperties(smartformControlProps, FormItems.Checkbox.SmartFormProperties);
				if (missingProps.length == 0)
				{ 			
					control = new FormItems.Checkbox(smartformControlProps);
				}
				else
				{
					throw new Error("Could not build checkbox form control ('" + smartformControlProps.description + "') - missing " + missingProps);
				}													
				break;
			}
			case 'radio': {
				var missingProps = FormItems.Util.checkRequiredProperties(smartformControlProps, FormItems.Radio.SmartFormProperties);
				if (missingProps.length == 0)
				{ 			
					control = new FormItems.Radio(smartformControlProps);
				}
				else
				{
					throw new Error("Could not build radio form control ('" + smartformControlProps.description + "') - missing " + missingProps);
				}																			
				break;
			}
			case 'suggest': {
				var missingProps = FormItems.Util.checkRequiredProperties(smartformControlProps, FormItems.SuggestField.SmartFormProperties);
				if (missingProps.length == 0)
				{ 			
					control = new FormItems.SuggestField(smartformControlProps);
				}
				else
				{
					throw new Error("Could not build suggest form control ('" + smartformControlProps.description + "') - missing " + missingProps);
				}								
				break;
			}				
			case 'verify': {
				var missingProps = FormItems.Util.checkRequiredProperties(smartformControlProps, FormItems.VerifyCombobox.SmartFormProperties);
				if (missingProps.length == 0)
				{ 			
					control = new FormItems.VerifyCombobox(smartformControlProps);
				}
				else
				{
					throw new Error("Could not build suggest verify control ('" + smartformControlProps.description + "') - missing " + missingProps);
				}								
				break;	
			}
			case 'number':{
				var missingProps = FormItems.Util.checkRequiredProperties(smartformControlProps, FormItems.NumberField.SmartFormProperties);
				if (missingProps.length == 0)
				{ 			
					control = new FormItems.NumberField(smartformControlProps)
				}
				else
				{
					throw new Error("Could not build number form control ('" + smartformControlProps.description + "') - missing " + missingProp);
				}										
				break;
			}
			case 'indicator':{
				var missingProps = FormItems.Util.checkRequiredProperties(smartformControlProps, FormItems.NumberField.IndicatorCheckbox);
				if (missingProps.length == 0)
				{ 			
					control = new FormItems.IndicatorCheckbox(smartformControlProps)
				}
				else
				{
					throw new Error("Could not build number indicator control ('" + smartformControlProps.description + "') - missing " + missingProp);
				}										
				break;
			}										
			default: {			
				throw new Error("Could not build form control ('" + smartformControlProps.description + "') - unknown controlType");
			}		
		}
	}
	
	return control;
}

SourcePageContainer = Ext.extend(PageContainer, {
	initComponent: function(){		
		SourcePageContainer.superclass.initComponent.apply(this, arguments);
		
		this.formLayout = this.initialConfig.formLayout;	
						
		for (var p = 0; p < this.initialConfig.images.length; p++)
		{		
			this.pages[p] = new Page({image: this.initialConfig.images[p]});
			this.pages[p].addClass('SourcePage')
			this.pages[p].correspondingFormPage = p;		
			this.pages[p].setTopOffset(64);
			this.pages[p].setLeftOffset(54);						
			this.add(this.pages[p]);
			
			this.pages[p].background.addListener('afterrender', this.afterBackgroundRender, this);
		}			
				
		if (this.formLayout)
		{
			this.addFormMarkup();
		}								
		
		this.prevPageBtn.addListener('click', function(){
			SmartFormsApp.PageNavigator.setSelectedPage('source', this.currentPageIndex - 1);
			}, this);
			
		this.nextPageBtn.addListener('click', function(){
			SmartFormsApp.PageNavigator.setSelectedPage('source', this.currentPageIndex + 1);
			}, this);		
	}
	
	,afterBackgroundRender: function(background)
	{
		var image = background.el.dom.firstChild;
		var page = background.ownerCt;
		
		image.style.filter = "progid:DXImageTransform.Microsoft.Matrix(M11='1.0', M12='0', M21='0', M22='1.0',, SizingMethod='auto expand') progid:DXImageTransform.Microsoft.BasicImage(grayscale=1, xray=0, mirror=0, invert=0, opacity=1, rotation=0)"
		image.style.zoom = 1;		
		
		page.rotateAngle = 0;
		page.rotateDirection = 0;
		page.magnification = 1;	
	}
	
	,clearFormMarkup: function()
	{
		for(var sourcePageIndex = 0; sourcePageIndex < this.pages.length; sourcePageIndex++)
		{
			this.pages[sourcePageIndex].contents.removeAll();
		}
	}
	
	,addFormMarkup: function()
	{
		var sourcePageIndex = 0;
		while (sourcePageIndex < this.pages.length)
		{			
			if (this.pages[sourcePageIndex].correspondingFormPage != null &&
				this.pages[sourcePageIndex].correspondingFormPage < this.formLayout.pages.length)
			{
				var formPageIndex = this.pages[sourcePageIndex].correspondingFormPage;				
				for (var s = 0; s < this.formLayout.pages[formPageIndex].sections.length; s++)
				{	
					var section = new FormItems.Section({
						y: this.formLayout.pages[formPageIndex].sections[s].top
						,height: this.formLayout.pages[formPageIndex].sections[s].height
					});
					
					for (var c = 0; c < this.formLayout.pages[formPageIndex].sections[s].controls.length; c++)
					{						
						section.add(SourcePageContainer.buildControlHighlight(this.formLayout.pages[formPageIndex].sections[s].controls[c]));	
					}					
										
					this.pages[sourcePageIndex].addToContents(section);												
				}
				this.pages[sourcePageIndex].doLayout();						
			}
			sourcePageIndex++;
		}				
	}
	
	,disablePage: function(index)
	{	
		this.pages[index].correspondingFormPage = null;
		
		var formPageIndex = 0;
		for (var sourcePageIndex = 0; sourcePageIndex < this.pages.length; sourcePageIndex++)		
		{
			if (this.pages[sourcePageIndex].correspondingFormPage != null)
			{
				this.pages[sourcePageIndex].correspondingFormPage = formPageIndex;
				formPageIndex++;
			}					
		}		
			
		this.clearFormMarkup();
		this.addFormMarkup();		
	}
	
	,enablePage: function(index)
	{
		this.pages[index].correspondingFormPage = -1;
		
		var formPageIndex = 0;
		for (var sourcePageIndex = 0; sourcePageIndex < this.pages.length; sourcePageIndex++)		
		{
			if (this.pages[sourcePageIndex].correspondingFormPage != null)
			{
				this.pages[sourcePageIndex].correspondingFormPage = formPageIndex;
				formPageIndex++;
			}					
		}		
		
		this.clearFormMarkup();
		this.addFormMarkup();
	}
	
	,rotateImage: function(direction, degreeVal)
	{
		var page = this.pages[this.currentPageIndex];
		degreeVal = (degreeVal == null ? 1 : degreeVal);
		
		if (direction > 0)
		{
			page.rotateAngle += degreeVal;
			page.rotateDirection--;
		}
		else
		{
			page.rotateAngle -= degreeVal;
			page.rotateDirection++;
		}
		page.rotateAngle %= 360;
		
		var rad = page.rotateAngle * (Math.PI * 2 / 360);
		var costheta = Math.cos(rad);
    	var sintheta = Math.sin(rad);

    	var img = page.background.el.dom.firstChild;
	    img.filters.item(0).M11 = costheta;
	    img.filters.item(0).M12 = -sintheta;
	    img.filters.item(0).M21 = sintheta;
	    img.filters.item(0).M22 = costheta;		
	    img.filters.item(0).SizingMethod = "auto expand";
	}
	
	,resizeImage: function(value)
	{
		var page = this.pages[this.currentPageIndex];
		var img = page.background.el.dom.firstChild;
		img.style.zoom = page.magnification + value;
		
		page.magnification = parseFloat(img.style.zoom);
	}
	
	,enableImageDrag: function()
	{
		var page = this.pages[this.currentPageIndex];
		var _self = this;
		var div = page.background.el.dom;
		div.style.cursor = 'pointer';
		div.onmousedown = function(evt){
			var evt = window.event; 
			_self.dragBackground(div, evt.x, evt.y)
		};		
	}
	
	,disableImageDrag: function()
	{
		var page = this.pages[this.currentPageIndex];		
		var div = page.background.el.dom;
		div.style.cursor = 'default';		
		div.onmousedown = null;
	}
	
	,dragBackground: function(background, startX, startY)
	{		
		var backgroundOrigPos = [background.offsetLeft, background.offsetTop];
		background.setCapture();
		background.attachEvent('onmousemove', moveHandler);
		background.attachEvent('onmouseup', upHandler);
		background.attachEvent('onlosecapture', upHandler);
		background.style.cursor = 'move';		
		
		function moveHandler()
		{
			var evt = window.event;						
			background.style.left = evt.x - (startX - backgroundOrigPos[0])
			background.style.top = evt.y - (startY - backgroundOrigPos[1])
			
			if ( evt.stopPropagation ) evt.stopPropagation();
        	else evt.cancelBubble = true; 
		}
		
		function upHandler()
		{
			var evt = window.event;					
			background.detachEvent('onmouseup', upHandler);
			background.detachEvent('onlosecapture', upHandler);
			background.detachEvent('onmousemove', moveHandler);
			background.releaseCapture();
			background.style.cursor = 'pointer';	
			
			if ( evt.stopPropagation ) evt.stopPropagation();
        	else evt.cancelBubble = true; 
		}
	}
	
	,getCorrespondingPageIndex: function(formPageIndex)
	{	
		var sourcePageIndex = null;	
		for (var p = 0; p < this.pages.length; p++)
		{					
			if (this.pages[p].correspondingFormPage == formPageIndex)			
			{
				sourcePageIndex = p;
			} 		
		}
		return sourcePageIndex;		
	}	
});

SourcePageContainer.buildControlHighlight = function(controlProps)
{
	var highlight = null;
	var highlightConfig = {		
		y: controlProps.top
		,x: controlProps.left
		,height: 20
		,width: controlProps.width
		,cls: 'ControlHighlight'
		,style: "display:" + (controlProps.dataMapping && controlProps.dataMapping != "" ? "block" : "none")						
	};
	
	if (controlProps.controlType == 'checkbox')
	{
		highlightConfig.height = 15;
		highlightConfig.width = 15;		
	}
	if (controlProps.controlType == 'radio')
	{
		highlightConfig.height = 15;
		highlightConfig.width = 15;		
	}		
	
	highlight = new Ext.BoxComponent(highlightConfig);
	
	return highlight;	
}


Page = Ext.extend(Ext.Container, {
	width: 600
	,height: 900	
		
	,initComponent: function(){
		this.leftOffset = 0;
		this.topOffset = 0;			
		this.width = this.initialConfig.image.width;
		this.height = this.initialConfig.image.height;
		this.pageType = this.initialConfig.pageType;
		this.index = this.initialConfig.index;
		
		var config = {			
			layout: 'absolute'
			,cls: 'Page'
			,style: 'overflow:hidden'				
		};
		
		Ext.apply(this, Ext.apply(this.initialConfig, config));	
		Page.superclass.initComponent.apply(this, arguments);
		
		this.background = new Ext.Container({
			height: this.height
			,width: this.width
			,style: 'overflow: hidden'
			,html: "<img src='" + this.initialConfig.image.uri + "'/>"
		});		
		this.add(this.background);
		
		this.contents = new Ext.Container({
			height: this.height
			,width: this.width
			,cls: 'hello'			
			,layout: 'absolute'			
		});
		this.add(this.contents);
	}
	,findFirstControl: function()
	{
		var sections = this.contents.items;		
		var control = null;
		for (var s = 0; s < sections.getCount(); s++)
		{						
			control = sections.get(s).findFirstControl();
			if (control != null)
			{
				break;
			}
		}
		return control;
	}
	
	,getSections: function()
	{
		return this.contents.items;
	}
	
	,getHeight: function()
	{
		return this.height;
	}
	
	,getWidth: function()
	{
		return this.width;
	}
	
	,setLeftOffset: function(val)
	{
		this.leftOffset = val;
	}
	
	,setTopOffset: function(val)
	{
		this.topOffset = val;
	}
	
	,getLeftOffset: function()
	{
		return this.leftOffset;
	}
	
	,getTopOffset: function()
	{
		return this.topOffset;
	}
	
	,addToContents: function(item)
	{
		this.contents.add(item);
		this.contents.doLayout();
	}
	
	,focus: function()
	{				
		var sections = this.getSections();
		for( var i = 0; i < sections.getCount(); i++)
		{
			var control = sections.get(i).focus();
			if (control != null)
			{				
				return control;
			}
		}
		return null;		
	}	
});