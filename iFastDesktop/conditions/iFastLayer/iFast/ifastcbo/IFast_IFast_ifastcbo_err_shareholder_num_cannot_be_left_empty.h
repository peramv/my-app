#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_shareholder_num_cannot_be_left_empty : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_shareholder_num_cannot_be_left_empty() { }
		~CIFast_IFast_ifastcbo_err_shareholder_num_cannot_be_left_empty() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SHAREHOLDER_NUM_CANNOT_BE_LEFT_EMPTY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The shareholder number must be entered.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Le numero d'actionnaire doit être saisi.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Die Aktionärs-Nummer muss eingegeben werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Debe introducirse el número de accionista.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le numéro d'actionnaire est requis.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Het aandeelhoudersnummer moet worden ingevoerd")); }

        // Actions
	};
}



