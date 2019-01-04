#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_dicore_dicore_datapath_reg_not_defined : public CConditionObject
	{
	public:
		CBase_Ifds_dicore_dicore_datapath_reg_not_defined() { }
		~CBase_Ifds_dicore_dicore_datapath_reg_not_defined() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DICORE_DATAPATH_REG_NOT_DEFINED")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("dicore")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The XML ‚ÌƒŠƒNƒGƒXƒg‚ÉƒtƒB[ƒ‹ƒhÚ×‚Ìƒ^ƒO‚ª‘½‰ß‚¬‚é")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Die XML-Nachfrage hat zu viele Felddetail-Kennzeichen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La solicitud XML tiene demasiadas etiquetas de detalles de campos")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le XML ?????N?G?X?g???t?B[???h?????^?O??‘???????")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("De XML-opdracht heeft te veel tags voor velddetails")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("XML‚ÌƒŠƒNƒGƒXƒg‚ðŠm”F‚µ‚Ä‰º‚³‚¢B")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("XML‚ÌƒŠƒNƒGƒXƒg‚ðŠm”F‚µ‚Ä‰º‚³‚¢?B")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("XML?????N?G?X?g???m”F??????????B")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("NULL")); }
	};
}



