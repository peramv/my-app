#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_cansim_not_exists : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_cansim_not_exists() { }
		~CIFast_IFast_ifastcbo_err_cansim_not_exists() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CANSIM_NOT_EXISTS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("CANSIM rate does not exist - please call the Supervisor.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("CANSIM-Rate existiert nicht - bitte rufen Sie das Organisationsprogramm auf.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La tasa CANSIM no existe. Por favor llame al supervisor.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Taux CANSIM inexistant – veuiller communiquer avec le superviseur.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("CANSIM-tarief bestaat niet - roep de supervisor")); }

        // Actions
	};
}



