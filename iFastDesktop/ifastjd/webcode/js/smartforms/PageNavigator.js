PageNavigator = Ext.extend(Ext.Panel, {	
	initComponent: function()
	{		
		var selectors = [];
		
		if (this.initialConfig.form)
		{
			this.formPageSelector = new PageSelector({
				title: 'Form Pages'
				,pageData: this.initialConfig.form
				,hidden: true
				,height: (this.initialConfig.source ? '50%' : '100%')
			});		
			this.formPageSelector.pageList.addListener('selectionchange', 
				function(){							
					this.fireEvent('pageselected', 
						{
							pageType: 'form', 
							pageIndex: this.formPageSelector.pageList.getSelectedIndexes()[0]
						}
					);
				},
				this
			);
			
			selectors[0] = this.formPageSelector;
		}
		
		if (this.initialConfig.source)
		{
			this.sourcePageSelector = new PageSelector({
				title: 'Source Pages' 
				,pageData: this.initialConfig.source
				,hidden: true 
				,height: '50%'
			});
			this.sourcePageSelector.pageList.addListener('selectionchange', 
				function(){							
					this.fireEvent('pageselected', 
						{
							pageType: 'source', 
							pageIndex: this.sourcePageSelector.pageList.getSelectedIndexes()[0]
						}
					);
				},
				this
			);
			this.sourcePageSelector.pageList.addListener('beforeclick', function(selector, index, node, evt){
					if (evt.ctrlKey)
					{						
						this.togglePageEnabled(index);																	
						return false;
					} 
				}
				,this
			);
			
			selectors[1] = this.sourcePageSelector;
		}
		
		var config = {
			region: 'west'
			,id: 'PageNavigator'			
			,width: 125			
			,border: false
			,style: 'border-right:1px solid #d0d0d0'
			,collapsible: true
			,layout: 'anchor'			
			,items: selectors	
		}
		
		Ext.apply(this, Ext.apply(this.initialConfig, config));	
		PageNavigator.superclass.initComponent.apply(this, arguments);
		
		this.addListener('pageselected', this.onPageSelected, this);
		
		SmartFormsApp.addListener('init', function(){
			if (this.sourcePageSelector)
			{
				for (var i = 0; i < SmartFormsApp.ContentViewer.sourcePageContainer.pages.length; i++)
				{
					if (SmartFormsApp.ContentViewer.sourcePageContainer.pages[i].correspondingFormPage != null)						
					{						
						this.sourcePageSelector.pageList.getNode(i).lastChild.className = "NumberOverlay";
						this.sourcePageSelector.pageList.getNode(i).lastChild.innerHTML = (i + 1);
						this.sourcePageSelector.pageList.getNode(i).enabled = true;	
					}
					else
					{						
						this.sourcePageSelector.pageList.getNode(i).lastChild.className = "NumberOverlay Disabled";
						this.sourcePageSelector.pageList.getNode(i).lastChild.innerHTML = "X";
						this.sourcePageSelector.pageList.getNode(i).enabled = false;
					}
				}
				this.sourcePageSelector.show();				
			}
			
			if (this.formPageSelector) 
			{
				this.formPageSelector.show();								
			}
		}, this);			
	}
	
	,togglePageEnabled: function(index)
	{
		var page = this.sourcePageSelector.pageList.getNode(index);
		if (page.enabled)
		{
			SmartFormsApp.ContentViewer.disableSourcePage(index);					
		}
		else
		{
			SmartFormsApp.ContentViewer.enableSourcePage(index);			
		}
		
		for (var i = 0; i < SmartFormsApp.ContentViewer.sourcePageContainer.pages.length; i++)
		{
			if (SmartFormsApp.ContentViewer.sourcePageContainer.pages[i].correspondingFormPage != null)				
			{						
				this.sourcePageSelector.pageList.getNode(i).lastChild.className = "NumberOverlay";
				this.sourcePageSelector.pageList.getNode(i).lastChild.innerHTML = (i + 1);
				this.sourcePageSelector.pageList.getNode(i).enabled = true;						
			}
			else
			{						
				this.sourcePageSelector.pageList.getNode(i).lastChild.className = "NumberOverlay Disabled";
				this.sourcePageSelector.pageList.getNode(i).lastChild.innerHTML = "X";
				this.sourcePageSelector.pageList.getNode(i).enabled = false;
			}
		}
	}
	
	,disablePageSelection: function(pageType)
	{
		if (pageType == 'form')
		{
			this.formPageSelector.pageSelectionEnabled = false;			
		}
		else if (pageType == 'source')
		{
			this.sourcePageSelector.pageSelectionEnabled = false;
		}
		else
		{
			this.formPageSelector.pageSelectionEnabled = false;
			this.sourcePageSelector.pageSelectionEnabled = false;
		}		
	}
	
	,enablePageSelection: function(pageType)
	{
		if (pageType == 'form')
		{
			this.formPageSelector.pageSelectionEnabled = true;
		}
		else if (pageType == 'source')
		{
			this.sourcePageSelector.pageSelectionEnabled = true;
		}
		else
		{
			this.formPageSelector.pageSelectionEnabled = true;
			this.sourcePageSelector.pageSelectionEnabled = true;
		}
	}
	
	,setSelectedPage: function(pageType, index)
	{		
		if (pageType == 'source')
		{
			if (this.sourcePageSelector)
			{			
				this.sourcePageSelector.pageList.select(index);
			}
		}
		else
		{
			if (this.formPageSelector)
			{
				this.formPageSelector.pageList.select(index);
			}
		}	
	}	
	
	,onPageSelected: function(pageInfo)
	{
		if (pageInfo.pageType == 'source')
		{
			this.sourcePageSelector.highlightPage(pageInfo.pageIndex);
			this.formPageSelector.highlightPage(null);
		}
		else
		{
			if (this.sourcePageSelector)
			{
				this.sourcePageSelector.highlightPage(null);
			}
			this.formPageSelector.highlightPage(pageInfo.pageIndex);
		}
	}
});


PageSelector = Ext.extend(Ext.Panel, {
	initComponent: function()
	{
		this.pageList = new Ext.DataView({
			cls: 'PageList'
			,singleSelect: true			
			,store: new Ext.data.Store(
				{
					autoLoad: false				
					,reader: new Ext.data.JsonReader(
						{						
							root: 'images'
							,fields: [							
								{name: 'uri'}
							]		
						}
					)
					,data: this.initialConfig.pageData
				}
			)
			,bubbleEvents: ['pageselect']
			,itemSelector: 'div.Page'
			,tpl: new Ext.XTemplate(											
				'<tpl for=".">'				
					,'<div class="Page">'
						,'<img class="PageImage" src="{uri}" />'
						,'<div class="NumberOverlay" style="" unselectable="on">{[xindex]}</div>' 
					,'</div>'				
				,'</tpl>'								
			)				
		});
		
		var config = {
			title: this.initialConfig.title		
			,autoScroll: true
			,bodyCssClass: 'PageSelector'
			,anchor: '100% ' + this.initialConfig.height		
			,items: [this.pageList]
		};
		
		Ext.apply(this, Ext.apply(this.initialConfig, config));	
		PageSelector.superclass.initComponent.apply(this, arguments);
					
		this.pageSelectionEnabled = true;
		
		this.pageList.addListener('beforeselect', function(){return this.pageSelectionEnabled}, this);
		this.pageList.addListener('containerclick', function(pageList, evt){return false});	
	}
		
	,highlightPage: function(index)
	{
		var dataStore = this.pageList.getStore();
		for (var i = 0; i < dataStore.getTotalCount(); i++)
		{
			var record = dataStore.getAt(i);
			if (i == index)
			{
				this.pageList.getNode(record).lastChild.style.filter = "alpha(opacity=70)";
			}
			else
			{
				this.pageList.getNode(record).lastChild.style.filter = "alpha(opacity=30)";
			}	
		}
	}
});

