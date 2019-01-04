/*********************************************************************************************
 * @file	ClassSetup_IntConfig.Resources.js	
 * @author	Rod Walker
 * @desc	Resources file for Interest Configuration screen, part of Class Setup flow
 *********************************************************************************************/
 /*
 * History : 
 *
 *    05 Mar 2014 G. Thawornwachirakun P0223930 FN01 DFT0030135 T54881 
 *             - Add ability to display French 
 */
 
DesktopWeb.ScreenResources = function(ctrlr)
{
	var _controller = ctrlr;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	
	// content dimensions
	var _layoutHeight = 670;
	var _layoutWidth = 750;
	
	var _header = new DesktopWeb.Controls.Label({															
		style: 'font-weight: bold; font-size: 13px; padding-bottom: 8px;'
		,height: 15
	})	
	
	var _breadCrumbList = new DesktopWeb.AdvancedControls.BreadCrumbList({						
		height: 45						
		,listeners: {
			itemclicked: function(id){_controller.changeScreen(id)}
		}
	})	
	
	// **** fields ****
	var _fields = {	
		simIRCode: new DesktopWeb.Controls.SMVComboBox({			
			fieldLabel: _translationMap['InterestRateCode']
			,width: 150
			,listeners: {
				select: function(){_controller.updateInterestRateGrid('sim')}
			}
		})
		,comIRCode: new DesktopWeb.Controls.SMVComboBox({
			fieldLabel: _translationMap['InterestRateCode']
			,width: 150
			,listeners: {
				select: function(){_controller.updateInterestRateGrid('com')}
			}
		})		 																																																							
	}
	
	// **** grids ****
	var _grids = {
		simInterestRate: new DesktopWeb.AdvancedControls.GridPanel({															
			autoScroll: true
			,columnWidth: 0.5
			,style: 'margin-bottom: 10px'							
			,height: 100
			,autoExpandColumn: 'value'			
			,disableSelection: true								
			,store: new Ext.data.XmlStore(
				{
					record: 'IntRateConfigDetl'					
					,fields: ['intSegment', 'value']											
				}
			)							
			,columns: [																																																							
				{header: _translationMap['InterestSegment'], dataIndex: 'intSegment', width:150}
				,{header: _translationMap['Value'], id: 'value', dataIndex: 'value'}				
			]								
		})
		
		,comInterestRate: new DesktopWeb.AdvancedControls.GridPanel({															
			autoScroll: true		
			,columnWidth: 0.5							
			,height: 100
			,style: 'margin-bottom: 10px'
			,autoExpandColumn: 'value'
			,disableSelection: true											
			,store: new Ext.data.XmlStore(
				{
					record: 'IntRateConfigDetl'					
					,fields: ['intSegment', 'value']											
				}
			)							
			,columns: [																																																							
				{header: _translationMap['InterestSegment'], dataIndex: 'intSegment', width:150}
				,{header: _translationMap['Value'], id: 'value', dataIndex: 'value'}				
			]									
		})
	}
	
	// **** popups ****
	var _popups = {					
	} 
	
	// PUBLIC ITEMS
	return {
		layoutWidth: _layoutWidth
		
		,layoutHeight: _layoutHeight

		,header: _header
		
		,breadCrumbList: _breadCrumbList
		
		,fields: _fields
		
		,grids: _grids
		
		,popups: _popups
		
		,layout: new Ext.Container(			
			{
				height: _layoutHeight
				,width: _layoutWidth
				,items: [
					_header
					,_breadCrumbList
					,new Ext.Container({
						style: 'padding-left:12px; padding-right:10px'
						,items: [
							{
								xtype: 'fieldset'
								,title: _translationMap['SimpleInterest']
								,items: [
									{										
										layout: 'column'																												
										,items: [
											{
												layout: 'form'
												,columnWidth: 0.5		
												,labelWidth: 160										
												,items: [_fields['simIRCode']]
											}
											,_grids['simInterestRate']																								
											
										]										
									}
								]
							}
							,{
								xtype: 'fieldset'
								,title: _translationMap['CompoundInterest']
								,items: [
									{										
										layout: 'column'										
										,items: [
											{
												layout: 'form'
												,columnWidth: 0.5
												,labelWidth: 160
												,items: [_fields['comIRCode']]
											}
											,_grids['comInterestRate']
										]										
									}
								]
							}
							
						]
					})	
				]
			}
		)
		
				,screenButtons: [
			new DesktopWeb.Controls.ScreenButton({
				text: _translationMap['Previous']
				,hidden: true
				,disabled: true				
				,id: 'prevBtn'
				,handler: function(){
					_controller.previous();
				}				
			})				
			,new DesktopWeb.Controls.ScreenButton({
				text: _translationMap['Save']
				,id: 'saveBtn'
				,disabled: true
				,handler: function(){
					_controller.save();	
				}								
			})
			,new DesktopWeb.Controls.ScreenButton({
				text: _translationMap['Reset']
				,id: 'resetBtn'
				,disabled: true
				,handler: function(){
					_controller.reset();	
				}								
			})
			,new DesktopWeb.Controls.ScreenButton({
				text: _translationMap['Cancel']
				,hidden: true				
				,id: 'cancelBtn'
				,handler: function(){
					_controller.cancel();
				}				
			})								
			,new DesktopWeb.Controls.ScreenButton({
				text: ''
				,hidden: true				
				,id: 'nextBtn'
				,handler: function(){
					_controller.next();
				}				
			})
			,new DesktopWeb.Controls.ScreenButton({
				text: _translationMap['ReturntoSummary']
				,hidden: true
				,id: 'summaryBtn'
				,handler: function(){
					_controller.changeScreen('Summary');
				}				
			})
		]	
	}
}