#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_contract_status : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_contract_status() { }
		~CIFast_IFast_ifastcbo_err_contract_status() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CONTRACT_STATUS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Contract status must be set to pending death claim before changing account status to death.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Contract status must be set to pending death claim before changing account status to death.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Vertragsstatus muss auf schwebenden Anspruch auf Sterbegeld gestellt werden, bevor der Kontostatus auf \"Tod\" gestellt wird.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El estado del contrato debe definirse como Reclamación por fallecimiento pendiente antes de cambiar su estado a Fallecimiento")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le statut du contrat doit être réglé à Sinistre-décès en suspens avant que vous ne changiez le statut du compte pour Décès.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Overeenkomststatus moet zijn ingesteld op wachtend op overlijdensclaim voordat de accountstatus in overleden kan worden gewijzigd")); }

        // Actions
	};
}



