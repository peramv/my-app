/*********************************************************************************************
 * @file	TaxForms.Resources.js
 * @author 	Narin Suanlamyai
 * @desc	Resources JS file for Tax Forms scree
 *********************************************************************************************/
/*
 * Procedure: TaxForms.Resources.js
 *
 * Purpose  : Resources of Tax Forms screen
 *             
 * Notes    : Open screens by COA -> Attributes Box -> Tax Forms
 *
 * History  : 
 *      12 Sep 2014 Narin Suanlamyai P0222874 - eDocs on iFastDesktop. 
 *                  - Created
 *                                    
 */
 
DesktopWeb.ScreenResources = function(ctrlr)
{
	var _controller = ctrlr;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	
	// content dimensions
	var _layoutHeight = 450;
	var _layoutWidth = 650;
	
	var disclaimerWidth = _layoutWidth - 200;
	
	// **** buttons ****
	var _buttons = {
		searchBtn: new DesktopWeb.Controls.ActionButton({																						
			text: _translationMap['Search']
			,listeners: {
				click: function(){_controller.clickHandle_searchBtn();}
			}
		})	
	}
	
	// **** fields ****
	var _fields = {
		taxYear: new DesktopWeb.Controls.SMVComboBox({
			fieldLabel: _translationMap['ReportingYear']
			,width: 100
			,allowBlank: false
			,editable: true
		})
		,disclm0: new DesktopWeb.Controls.Label({
			width: _layoutWidth - 12
			,hideLabel: true
			,text: _translationMap['Disclaimer']
		})
		,disclm1: new DesktopWeb.Controls.Label({
			width: disclaimerWidth
			,hideLabel: true
			,text: _translationMap['Disclaimer1']
			,style: 'padding-bottom:10px;'
		})
		,disclm2: new DesktopWeb.Controls.Label({
			width: disclaimerWidth
			,hideLabel: true
			,text: _translationMap['Disclaimer2']
		})
		,disclm3: new DesktopWeb.Controls.Label({
			width: disclaimerWidth
			,hideLabel: true
			,text: _translationMap['Disclaimer3']
		})
	}
	
	// **** grids ****
	var _grids = {
		taxForms: new DesktopWeb.AdvancedControls.GridPanel(
			{							
				width: _layoutWidth - 12
				,autoScroll: true
				,height: 200
				,autoExpandColumn: 'formType'
				,store: new Ext.data.XmlStore(
					{
						record: 'TaxFormInfo'
						,fields: ['formType', 'formLink', 'issdCnclDt', 'stat', 'procDate', 'txPComRid'
									, 'interfaceName', 'isManual']
						,listeners: {
							load: function(store, records)
							{
								Ext.each(records, function(record){
									record.data.issdCnclDt = DesktopWeb.Util.getDateDisplayValue(record.data.issdCnclDt);
									record.data.procDate = DesktopWeb.Util.getDateDisplayValue(record.data.procDate);
								});
								store.fireEvent('datachanged', store); //to set data in grid again
							}
						}
					}
				)
				,selModel: new Ext.grid.RowSelectionModel(
					{
						singleSelect: true
						,listeners: {
							rowselect: function(selModel, index, record){
								if(selModel){
									_controller.selectTaxForm(record);
								}
							}
						}
					}
				)
				,colModel: new Ext.grid.ColumnModel(
					{
						defaults: {
							menuDisabled: true
							,sortable: false
						}
						,columns: [
							{id: 'formType', header: _translationMap['TaxFormType'], dataIndex: 'formType'}
							,{header: _translationMap['IssuedDateCancelledDate'], dataIndex: 'issdCnclDt' , width: 200}
							,{header: _translationMap['TaxFormStatus'], dataIndex: 'stat', width: 200}
							
						]							
					}
				)
				,buttons: [
					new DesktopWeb.Controls.ActionButton(
						{
							itemId: 'pdfBtn'
							,text: _translationMap['ViewPDF']
							,disabled: true
							,handler: function(btn){_controller.clickHandle_pdfBtn();}
						}
					)
					,new DesktopWeb.Controls.ActionButton(
						{
							itemId: 'moreBtn'
							,text: _translationMap['More']
							,disabled: true
							,handler: function(){_controller.clickHandle_moreBtn();}
						}
					)
				]
			}
		)
	}
	
	// **** popups ****
	var _popups = {} 
	
	// PUBLIC ITEMS
	return {
		layoutWidth: _layoutWidth
		
		,layoutHeight: _layoutHeight
		
		,buttons: _buttons
		
		,fields: _fields
		
		,grids: _grids
		
		,popups: _popups
		
		,layout: new Ext.Container(			
			{
				height: _layoutHeight
				,width: _layoutWidth
				,style: 'padding-left:5px; padding-right:5px;'
				,items: [
					{
						// Search section
						layout: 'column'
						,defaults: {
							layout: 'form'
							,labelWidth: 131
						}
						,items: [
							{								
								columnWidth: 0.4
								,items: [
									_fields['taxYear']
								]
							}
							,{
								columnWidth: 0.6
								,items: [
									_buttons['searchBtn']
								]
							}
						]
					}
					,_grids['taxForms']
					//,_fields['disclm0']
					,{
						layout: 'form'
						,defaults: {
							style: 'padding-bottom:10px;'
						}
						,items: [
							_fields['disclm1']
							,_fields['disclm2']
							,_fields['disclm3']
						]
					}
				]																				
			}
		)
		
		,screenButtons: [			
			new DesktopWeb.Controls.ScreenButton(
				{
					text: _translationMap['Close']
					,handler: function(){
						DesktopWeb.Util.cancelScreen();
					}
				}
			)
		]			
	}
}