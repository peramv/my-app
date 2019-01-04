#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_shareholder_deceased : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_shareholder_deceased() { }
		~CIFast_IFast_ifastcbo_err_shareholder_deceased() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SHAREHOLDER_DECEASED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("This shareholder is deceased. No LLP repayments allowed.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Dieser Aktionär ist verstorben. LLP-Rückzahlungen nicht erlaubt.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Este accionista ha fallecido. No se permiten reembolsos de LLP.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Cet actionnaire est décédé. Aucun remboursement REEP n'est autorisé.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Deze aandeelhouder is overleden. Er zijn geen LLP-terugbetalingen toegestaan")); }

        // Actions
	};
}



