#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_banking_idype_mandatory_for_pac : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_banking_idype_mandatory_for_pac() { }
		~CIFast_IFast_ifastcbo_err_banking_idype_mandatory_for_pac() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_BANKING_IDYPE_MANDATORY_FOR_PAC")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("PAC setup using %FILE_PROC% requires banking instructions of ID Type %IDTYPE%  for collection.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La mise en œuvre de la PAC à l’aide de %FILE_PROC% nécessite des instructions bancaires du type de numéro d'identification %IDTYPE% aux fins de perception.")); }

        // Actions
	};
}



