#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_cnfrm_freq : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_cnfrm_freq() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_cnfrm_freq() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_INVALID_CNFRM_FREQ")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Secondary Beneficiary Entity only allowed if Primary Entity exist and Beneficial Percentage total up to 100%.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Secondary Beneficiary Entity only allowed if Primary Entity exist and Beneficial Percentage total up to 100%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Zweites Begünstigten-Objekt ist nur zugelassen, wenn ein erstes Objekt existiert und der  Prozentsatz zusammen 100% beträgt.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Sólo se permite entidad Beneficiario secundario si existe una entidad Principal y el porcentaje beneficiario es de hasta 100%")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Une entité bénéficiaire secondaire n'est autorisée que si une entité primaire existe et que le pourcentage bénéficiaire totalise 100 %.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Eenheid tweede begunstigde is alleentoegestaan als eerste eenheid bestaat en begunstigdepercentage in totaal 100% bedraagt")); }

        // Actions
	};
}



