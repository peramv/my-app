#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_no_company_record : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_no_company_record() { }
		~CIFast_IFast_ifastdbrkr_err_no_company_record() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NO_COMPANY_RECORD")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Access denied - no company record.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Access denied - no company record.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Zugriff verweigert – kein Unternehmenseintrag")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Acceso denegado - No hay registro de la compañía.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Accès refusé – aucun enregistrement d'entreprise")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Toegang geweigerd - geen bedrijfsrecord")); }

        // Actions
	};
}



