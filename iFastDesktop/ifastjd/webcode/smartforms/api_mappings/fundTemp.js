API.fundTemp = {};

API.fundTemp = {
	type: 'node'		
	,isRequired: function(){return true}	
	,contents: {
		FundInfo: {
			type: 'node'
			,isRequired: function(){return false}
			,repeatCount: 10			
			,contents: {
				fundIDType: {
					type: 'field'						
					,dataType: 'string'
					,isRequired: function(node){return false}				
					,description: 'Type of fund identifier'
				}				
				,fundIDValue: {
					type: 'field'						
					,dataType: 'string'
					,isRequired: function(){return false}				
					,description: 'Fund identifier'
				}
				,fundIDDesc: {
					type: 'field'
					,dataType: 'string'
					,isRequired: function(){return false}
					,description: 'Fund Identifier'	
				}
			}
		}
	}		
}
