/*********************************************************************************************
 * @file	SegEventDates.Resources.js
 * @author	Matira Thanetkulabut
 * @desc	Resources file for SEG Dates screen
 *********************************************************************************************/
/*
 *  Navigate: Menu > Account > Contract Information > SEG Dates
 *  
 *  History : 
 *  
 *  26-Sep-2016 Matira Thanetkulabut P0256533 T84091 MSF - Desktop
 *              - Initial
 */
 
DesktopWeb.ScreenResources = function(ctrlr)
{
    var _controller = ctrlr;
    var _translationMap = DesktopWeb.Translation.getTranslationMap();
    
    // content dimensions
    var _layoutHeight = 300;
    var _layoutWidth  = 400;

    // **** fields **** 
    var _fields = {
    }
    
    // **** buttons ****
	var _buttons = {
    }
    
    // **** grids ****
	var _grids = {
        segDate: new DesktopWeb.AdvancedControls.GridPanel(
        {
            height: 300
            ,autoExpandColumn: 'eventName'
            ,autoScroll: true
            ,store: new Ext.data.XmlStore(
            {
                record: 'SEGDate'
                ,fields: ['eventName', 'eventDate']
                ,listeners: 
                {
                    load: function(store, records)
                    {		
                        Ext.each(records, function(record)
                        {
                            record.data.eventDate = DesktopWeb.Util.getDateDisplayValue(record.data.eventDate);
                        });
                        
                        store.fireEvent('datachanged', store);
                    }
                }
            })
            ,colModel: new Ext.grid.ColumnModel(
            {
                defaults: { menuDisabled: true }
                ,columns: [
                {
                    header: _translationMap['Description']
                    ,id: 'eventName'
                    ,width: 100
                    ,dataIndex: 'eventName'
                }
                ,{
                    header: _translationMap['Dates']
                    ,width: 80
                    ,dataIndex: 'eventDate' 
                }]
            })
        })
    }
    
    // **** popups ****
    var _popups = {
    }
    
     // PUBLIC ITEMS
    return {
        layoutWidth: _layoutWidth

        ,layoutHeight: _layoutHeight

        ,fields: _fields

        ,grids: _grids

        ,popups: _popups

        ,buttons: _buttons

        ,layout: new Ext.Container(
        {
            height: _layoutHeight
            ,width: _layoutWidth
            ,items: [_grids['segDate']]
        })
        
        ,screenButtons: [
            new DesktopWeb.Controls.ScreenButton({
                text: _translationMap['Close']
                ,handler: function(){
                    DesktopWeb.Util.cancelScreen();
                }
            })
        ]
    }
}