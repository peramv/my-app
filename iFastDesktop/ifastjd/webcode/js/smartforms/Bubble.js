Bubble = Ext.extend(Ext.Window, {
	initComponent: function()
	{
		 var config = {		 			 
		 	height: 100
			,width: 100
			,minHeight: 100
			,minWidth: 100
			//,resizeHandles: 's e se'
			,draggable: false
			,layout: 'absolute'
			,autoScroll: false
			,cls: 'Bubble'
			,closeAction: 'hide'			
		};
		
		Ext.apply(this, Ext.apply(this.initialConfig, config));	
		Bubble.superclass.initComponent.apply(this, arguments);
		
		this.addListener('afterrender', this.onAfterRender, this);
		this.addListener('afterlayout', this.onAfterLayout, this);	
	}
	
	,onRender: function(ct, position)
	{
		Bubble.superclass.onRender.call(this, ct, position);
	}
	
	,onAfterRender: function()
	{
		var top_anchor = document.createElement('div');
		top_anchor.id = 'anchor_top';
		top_anchor.className = 'anchor_top'				 		
		this.el.appendChild(top_anchor);
		
		var bottom_anchor = document.createElement('div');
		bottom_anchor.id = 'anchor_bottom';
		bottom_anchor.className = 'anchor_bottom'				 		
		this.el.appendChild(bottom_anchor);		
	}
	
	,onAfterLayout: function()
	{
		var anchor_bottom = document.getElementById("anchor_bottom");
		if (anchor_bottom)
		{		
			anchor_bottom.style.top = this.getHeight() - 5;
		}
	}
});


SourceBubble = Ext.extend(Bubble, {
	initComponent: function()
	{		
		SourceBubble.superclass.initComponent.apply(this, arguments);
		
		this.sourcePageContainer = new SourcePageContainer({
			images: this.initialConfig.images
			,formLayout: this.initialConfig.formLayout					
		});
		this.add(this.sourcePageContainer);
		this.sourcePageContainer.prevPageBtn.hide();
		this.sourcePageContainer.nextPageBtn.hide();
		
		this.sourcePageContainer.addListener('click', this.dragSourcePage, this);
		
		this.currentPageIndex = null;
		this.currentItem = null;
		this.sectionsEnabled = false;
	}
	
	,enableSections: function()
	{
		this.sectionsEnabled = true;
		if (this.isVisible())
		{			
			this.redisplay();			
		}
	}
	
	,disableSections: function()
	{		
		this.sectionsEnabled = false;		
		if (this.isVisible())
		{
			this.redisplay();			
		}
	}
			
	,setDisplay: function(pageIndex, item)
	{
		this.currentPageIndex = pageIndex;
		this.currentItem = item;
		
		this.redisplay();
	}
	
	,dragSourceContainer: function(container, startX, startY)
	{		
		var containerOrigPos = [container.offsetLeft, container.offsetTop];
		container.setCapture();
		container.attachEvent('onmousemove', moveHandler);
		container.attachEvent('onmouseup', upHandler);
		container.attachEvent('onlosecapture', upHandler);
		container.style.cursor = 'move';		
		
		function moveHandler()
		{
			window.status = this.currentPageIndex;
			var evt = window.event;						
			container.style.left = evt.x - (startX - containerOrigPos[0])
			container.style.top = evt.y - (startY - containerOrigPos[1])
			
			if ( evt.stopPropagation ) evt.stopPropagation();
        	else evt.cancelBubble = true; 
		}
		
		function upHandler()
		{
			var evt = window.event;					
			container.detachEvent('onmouseup', upHandler);
			container.detachEvent('onlosecapture', upHandler);
			container.detachEvent('onmousemove', moveHandler);
			container.releaseCapture();
			container.style.cursor = 'pointer';	
			
			if ( evt.stopPropagation ) evt.stopPropagation();
        	else evt.cancelBubble = true; 
		}
	}
	
	,redisplay: function()
	{	
		var positionDetails = {top: null, left: null};
		var dimensionDetails = {height: null, width: null};
		var anchorPosition = null;
		var bubbleTitle = null;
		
		var pageHeight = this.sourcePageContainer.pages[this.currentPageIndex].getHeight();
		
		if (this.sectionsEnabled)
		{
			var section = FormItems.Util.getContainerSection(this.currentItem);
			dimensionDetails.height = (section.getHeight() + 25 > 80 ? section.getHeight() + 25 : 80);
			dimensionDetails.width = section.getWidth() + 20;
			
			positionDetails.left = section.getPosition()[0] - 10;			
			if (this.currentItem.getPosition()[1] < pageHeight/2)
			{
				positionDetails.top = section.getPosition()[1] + section.getHeight() + 10;
				anchorPosition = 'top';
			}
			else
			{
				positionDetails.top = section.getPosition()[1] - dimensionDetails.height - 20;
				anchorPosition = 'bottom';
			}			
		}
		else
		{
			dimensionDetails.height = 95;
			dimensionDetails.width = (this.currentItem.getWidth() > 100 ? this.currentItem.getWidth() + 30 : 100);
			
			positionDetails.left = this.currentItem.getPosition()[0] - 10;
			if (this.currentItem.getPosition()[1] < pageHeight/2)
			{
				positionDetails.top = this.currentItem.getPosition()[1] + this.currentItem.getHeight() + 10;
				anchorPosition = 'top';
			}
			else
			{
				positionDetails.top = this.currentItem.getPosition()[1] - dimensionDetails.height - 10;
				anchorPosition = 'bottom';
			}		
		}
		
		this.setHeight(dimensionDetails.height);
		this.setWidth(dimensionDetails.width);
		this.setPagePosition(positionDetails.left, positionDetails.top);
		if (anchorPosition == 'top')
		{
			document.getElementById('anchor_top').style.visibility = 'visible';
			document.getElementById('anchor_bottom').style.visibility = 'hidden';
		}
		else
		{
			document.getElementById('anchor_top').style.visibility = 'hidden';
			document.getElementById('anchor_bottom').style.visibility = 'visible';
		}
		
		var sourcePos_left = null;													
		var sourcePos_top = null; 
		if (this.sectionsEnabled)
		{
			var section = FormItems.Util.getContainerSection(this.currentItem);
			sourcePos_left = 0;													
			sourcePos_top = (isNaN(parseInt(section.getResizeEl().dom.style.top)) ? 0 : parseInt(section.getResizeEl().dom.style.top))
		}									
		else
		{
			sourcePos_left = FormItems.Util.getControlPagePosition(this.currentItem)[0] - 5;													
			sourcePos_top = FormItems.Util.getControlPagePosition(this.currentItem)[1] - 20;
		}
		
		this.sourcePageContainer.show();		
		this.sourcePageContainer.showPage(this.currentPageIndex)
						
		this.sourcePageContainer.pages[this.currentPageIndex].setPosition( -1 * sourcePos_left, -1 * sourcePos_top);
				
		this.setTitle("<i>" + this.currentItem.dataStoreNode.apiReference.description + "</i>");
		
		
		var _self = this;
		var div = this.sourcePageContainer.el.dom;
		div.style.cursor = 'pointer';
		div.onmousedown = function(evt){			
			var evt = window.event; 
			_self.dragSourceContainer(div, evt.x, evt.y, _self)
		};		
		div.style.left = 0;
		div.style.top = 0;
	}
	
	,setBackgroundPosition: function(pageIndex, top, left)
	{
		var page = this.sourcePageContainer.pages[pageIndex]
		page.background.el.dom.style.top = top;
		page.background.el.dom.style.left = left;		
	}
	
	,disablePage: function(index)
	{
		this.sourcePageContainer.disablePage(index);
		if (this.isVisible())
		{			
			this.redisplay();			
		}
	}
	
	,enablePage: function(index)
	{
		this.sourcePageContainer.enablePage(index);
		if (this.isVisible())
		{			
			this.redisplay();			
		}
	}
});
