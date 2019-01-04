API.gnCotSetupRequest = {};

API.gnCotSetupRequest = {
	type: 'node'
	,isRequired: function(){return false}
	,description: 'Contract Setup'		
	,contents: {
		CotSetup: {
			type: 'node'
			,isRequired: function(){return true}	
			,contents: {
				contractType: {
					type: 'field'						
					,dataType: 'listValue'
					,isRequired: function(){return true}				
					,description: 'Contract Type'
					,listName: 'ContractType'
				}
				,effDate: {
					type: 'field'						
					,dataType: 'date'
					,isRequired: function(){return false}				
					,description: 'Eff. Date'
				}
				,maturityDate: {
					type: 'field'						
					,dataType: 'date'
					,isRequired: function(){return false}				
					,description: 'Maturity Date'
				}
				,stopDate: {
					type: 'field'						
					,dataType: 'date'
					,isRequired: function(){return false}				
					,description: 'Contract Stop Date'
				}
				,provReg: {
					type: 'field'						
					,dataType: 'string'
					,isRequired: function(){return false}				
					,description: 'Contract Prov'
				}
				,inclJntLifeEnt: {
					type: 'field'						
					,dataType: 'string'
					,isRequired: function(){return false}				
					,description: 'Include Joint Life Entity?'
				}
				,accountidtgroup: {
					type: 'node'
					,isRequired: function(){return false}	
					,contents: {
						accountIDType: {
							type: 'field'						
							,dataType: 'string'
							,isRequired: function(){return true}				
							,description: 'account id'
						}
						,accountIDValue: {
							type: 'field'						
							,dataType: 'string'
							,isRequired: function(){return true}				
							,description: 'IFAST Account Number'
						}
					}
				}
				,JntLifeEnt: {
					type: 'node'
					,isRequired: function(){return false}	
					,description: 'required when inclJntLifeEnt is yes'	
					,contents: {
						ClientInfo: {
							type: 'node'
							,isRequired: function(){return true}
							,contents: {
								Individual: {
									type: 'node'
									,isRequired: function(){return true}
									,contents: {
										titleCode: {
											type: 'field'						
											,dataType: 'string'
											,isRequired: function(){return false}				
											,description: 'Title Code'
										}
										,firstName: {
											type: 'field'						
											,dataType: 'string'
											,isRequired: function(){return false}				
											,description: 'First Name'
										}
										,lastName: {
											type: 'field'						
											,dataType: 'string'
											,isRequired: function(){return true}				
											,description: 'Last Name'
										}
										,SIN: {
											type: 'field'						
											,dataType: 'string'
											,isRequired: function(){return false}				
											,description: 'SIN'
										}
										,birthDate: {
											type: 'field'						
											,dataType: 'date'
											,isRequired: function(){return true}				
											,description: 'Birth Date'
										}
										,gender: {
											type: 'field'						
											,dataType: 'string'
											,isRequired: function(){return false}				
											,description: 'Gender'
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
};

