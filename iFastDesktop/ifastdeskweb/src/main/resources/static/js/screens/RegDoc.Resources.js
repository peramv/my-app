/*********************************************************************************************
 * @file	RegDoc.Resources.js
 * @author	Manoj Kumar
 * @desc	Resources JS file for Regulatory Documents screen
 *
 * Feb 24, 2014      Supareuk Sukjaitham PETP0223930 FN01 DFT0029203 T54832
 *                   Foreign Account Tax Compliance Act
 *                   (FATCA) Phase 1C - Entity Level
 *                   - Increase size of TaxImpact and TaxExempt dropdown
 *                   - Decrease size of description box
 *********************************************************************************************/
 /*
 * History : 
 *
 *  05 Mar 2014 G. Thawornwachirakun P0223930 FN01 DFT0030135 T54881 
 *             - Add ability to display French 
 *
 *  18 Nov 2014 Winnie Cheng P0247899  T81687 
 *             - Desktop Screen Regulatory Documents modification.
 *             - Be able to retrive more records by providing "More" button.
 *    
 */
 
DesktopWeb.ScreenResources = function(ctrlr)
{
	var _controller = ctrlr;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	
	// content dimensions
	var _layoutHeight = 240;
	var _layoutWidth = 750
	
	// **** fields ****
	var _fields = {
	}
	
	// **** grids ****
	var _grids = {
		regDocInfo: new DesktopWeb.AdvancedControls.GridPanel({
			width: _layoutWidth
			,style: "margin-bottom:15px"
			,autoScroll: true
			,height: 225
			,autoExpandColumn: 'docDesc'
			//,deferRowRender: true
			,store: new Ext.data.XmlStore({
				record: 'DocItem'
				,fields: ['docCode', 'description', 'taxImpact', 'taxImpactDesc','taxJuris', 'taxJurisDesc','taxExType','taxExTypeDesc']
			})
			,selModel: new Ext.grid.RowSelectionModel({
				singleSelect: true
				,listeners: {
					rowselect: function(selModel, index, record){_controller.updateActionButtons();}
					,rowdeselect: function(){_controller.updateActionButtons();}
				}
			})
			,colModel: new Ext.grid.ColumnModel({
				defaults: {
					menuDisabled: true
				}
				,columns: [
					{header: _translationMap['DocCode'], dataIndex: 'docCode', width:100}
					,{header: _translationMap['Description'], id:'docDesc', dataIndex: 'description'}
					,{header: _translationMap['TaxImpact'], id:'taxImpact', dataIndex: 'taxImpactDesc'  
				}
					,{header: _translationMap['TaxJurisdiction'], id:'taxJuris', dataIndex: 'taxJurisDesc'}
					,{header: _translationMap['TaxExType'], id:'taxExType', dataIndex: 'taxExTypeDesc'}
				]
			})
			,buttons: [					
				new DesktopWeb.Controls.ActionButton({
					itemId: 'addBtn'								
					,text: _translationMap['Add']
					,handler: function(){_controller.openActionPopup(_controller.ADD);}
				})
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'modBtn'
					,text: _translationMap['Modify']
					,handler: function(){_controller.openActionPopup(_controller.MOD);}
				})
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'delBtn'
					,text: _translationMap['Delete']
					,handler: function(){_controller.openActionPopup(_controller.DEL);}
				})		
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'moreBtn'
					,text: _translationMap['More']
					,handler: function(){_controller.clickHandleMoreBtn();}
				})						
			]			
		})		
	}
	
	// **** popups ****
	var _popups = {			
		regDoc: new DesktopWeb.AdvancedControls.PopupWindow({				
			width: 510
			,action: null
			,modal: true	
			,defaults: {border:false}
			,items: [
				{
					html: _translationMap['DeleteConfirmMsg']							
					,style: 'text-align:center'														
				}						
				,{						
					layout: 'form'																		
					,style: 'padding:4px'
					,labelWidth: 120
					,items: [
						new DesktopWeb.Controls.TextField({
							itemId: 'docCode'							
							,width: 340
							,fieldLabel: _translationMap['DocCode']
							,style: 'text-transform: none'
							,allowBlank: false														
						})											
						,new DesktopWeb.Controls.TextField({
							itemId: 'docDesc'	
							,width: 340
							,fieldLabel: _translationMap['Description']
							,style: 'text-transform: none'
							,allowBlank: false														
						})
						,new DesktopWeb.Controls.SMVComboBox({
							itemId: 'taxImpact'	
							,width: 340
							,fieldLabel: _translationMap['TaxImpact']
							,style: 'text-transform: none'
							,listeners:{
								select : function(fld, rec, index){
									_popups['regDoc'].getField('taxJuris').enable();
									_popups['regDoc'].getField('taxExType').enable();
								}
							}
						})		
						,new DesktopWeb.Controls.SMVComboBox({
							itemId: 'taxJuris'	
							,width: 340
							,fieldLabel: _translationMap['TaxJurisdiction']
							,style: 'text-transform: none'
							,disabled : true
						})		
						,new DesktopWeb.Controls.SMVComboBox({
							itemId: 'taxExType'	
							,width: 340
							,fieldLabel: _translationMap['TaxExType']
							,style: 'text-transform: none'
							,disabled : true
						})		

					]												
				}													
			]
			,buttons: [
				new DesktopWeb.Controls.ActionButton({
					text: _translationMap['OK']
					,handler: function(){
						if (_popups['regDoc'].isValid())
						{
							_controller.savePopup(_popups['regDoc'].action, _popups['regDoc'].getData());
						}
					}	
				})
				,new DesktopWeb.Controls.ActionButton({
					text: _translationMap['Cancel']
					,handler: function(){_popups['regDoc'].hide();}
				})
			]
			,init: function(action)
			{										
				this.action = action					
				this.clearAllFields();
				this.get(0).hide(); //hide delete message
				switch(action)
				{
					case _controller.ADD:
					{
						this.setTitle(_translationMap['RegulatoryDocument'] + ' - ' + _translationMap['Add']);
						this.enableAllFields();													
						this.getField('docCode').focus();							
						break;
					}
					case _controller.MOD:
					{
						this.setTitle(_translationMap['RegulatoryDocument'] + ' - ' + _translationMap['Modify']);
						this.enableAllFields();
						this.getField('docCode').disableField();
						this.populateWithSelectedRecord();													
						this.getField('docCode').focus();				
						break;
					}
					case _controller.DEL:
					{
						this.setTitle(_translationMap['RegulatoryDocument'] + ' - ' + _translationMap['Delete']);
						this.get(0).show();  
						this.disableAllFields();							
						this.populateWithSelectedRecord();												
						break;
					}
				}														
			}
			,clearAllFields: function()
			{											
				this.getField('docCode').setValue('');
				this.getField('docDesc').setValue('');
				this.getField('taxImpact').setValue('');
				this.getField('taxJuris').setValue('');
				this.getField('taxExType').setValue('');					
			}
			,populateWithSelectedRecord: function()
			{
				var rec = _grids['regDocInfo'].getSelectedRecord();				
				this.getField('docCode').setValue(rec.data['docCode']);
				this.getField('docDesc').setValue(rec.data['description']);
				this.getField('taxImpact').setValue(rec.data['taxImpactDesc']);
				this.getField('taxJuris').setValue(rec.data['taxJurisDesc']);
				this.getField('taxExType').setValue(rec.data['taxExTypeDesc']);

			}
			,getData: function()
			{
				var data = {};		
				data['runMode'] = this.action;
				data['docCode'] = this.getField('docCode').getValue();
				data['description'] = this.getField('docDesc').getValue();
				if (this.getField('taxImpact').getValueDesc() != null) {
					data['taxImpactDesc'] = this.getField('taxImpact').getValueDesc();
				} else {
					data['taxImpactDesc'] = this.getField('taxImpact').getValue();
				}
				if (this.getField('taxJuris').getValueDesc() != null) {
					data['taxJurisDesc'] = this.getField('taxJuris').getValueDesc();
				} else {
					data['taxJurisDesc'] = this.getField('taxJuris').getValue();
				}
				if (this.getField('taxExType').getValueDesc() != null) {
					data['taxExTypeDesc'] = this.getField('taxExType').getValueDesc();
				} else {
					data['taxExTypeDesc'] = this.getField('taxExType').getValue();
				}
				return data;
			}														
		})
	} 
	
	// PUBLIC ITEMS
	return {
		layoutWidth: _layoutWidth
		
		,layoutHeight: _layoutHeight
		
		,fields: _fields
		
		,grids: _grids
		
		,popups: _popups
		
		,layout: new Ext.Container(			
			{
				height: _layoutHeight
				,width: _layoutWidth																
				,items: [
					_grids['regDocInfo']																	
				]				
			}
		)
		
		,screenButtons: [			
			new DesktopWeb.Controls.ScreenButton(
				{
					text: _translationMap['Close']
					,handler: function(){DesktopWeb.Util.cancelScreen()}
				}
			)
		]			
	}
}	