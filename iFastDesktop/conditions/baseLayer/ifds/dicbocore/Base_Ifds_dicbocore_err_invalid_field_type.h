#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_dicbocore_err_invalid_field_type : public CConditionObject
	{
	public:
		CBase_Ifds_dicbocore_err_invalid_field_type() { }
		~CBase_Ifds_dicbocore_err_invalid_field_type() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_FIELD_TYPE")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("dicbocore")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Encorr Memory Allocation Error.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Encorr Memory Allocation Error.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Automatische Transfers können für ein Escrow-(Ander)konto nicht erstellt werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Encorr Memory Allocation Error.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Erreur d'attribution de mémoire Encorr")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Fout bij toewijzen Encorr-geheugen.")); }

        // Actions
		virtual DString GetAction_ES_ES() const { return DString(I_("NULL")); }
	};
}



