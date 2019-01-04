API.bankTemp = {};

API.bankTemp = {
	type: 'node'		
	,isRequired: function(){return true}	
	,contents: {
		BkInfo: {
			type: 'node'
			,isRequired: function(node){return node.hasData()}
			,description: 'Banking Info.'
			,contents: {
				instutNum: {
					type: 'field'
					,dataType: 'string'
					,isRequired: function(){return true}
					,description: 'Institution Code'
				}
				,branchNum: {
					type: 'field'
					,dataType: 'string'
					,isRequired: function(){return true}
					,description: 'Transit Number'
				}
				,bkAcctType: {
					type: 'field'
					,dataType: 'listValue'
					,isRequired: function(){return false}
					,description: 'Bank account type'
					,listName: 'bkAcctType'
				}
				,bkAcctNum: {
					type: 'field'
					,dataType: 'string'
					,isRequired: function(){return true}
					,description: 'Bank account number'
				}
				,currency: {
					type: 'field'
					,dataType: 'string'
					,isRequired: function(){return false}
					,description: 'Bank account currency'
				}
				,holder: {
					type: 'field'
					,dataType: 'string'
					,isRequired: function(){return false}
					,description: 'Name of the holder'
				}	
			}			
		}
	}
}
