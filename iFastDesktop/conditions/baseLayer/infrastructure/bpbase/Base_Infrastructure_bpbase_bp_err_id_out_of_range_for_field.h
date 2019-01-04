#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Infrastructure_bpbase_bp_err_id_out_of_range_for_field : public CConditionObject
	{
	public:
		CBase_Infrastructure_bpbase_bp_err_id_out_of_range_for_field() { }
		~CBase_Infrastructure_bpbase_bp_err_id_out_of_range_for_field() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("BP_ERR_ID_OUT_OF_RANGE_FOR_FIELD")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("bpbase")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The system does not recognize this certificate number.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("The system does not recognize this certificate number.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Das System erkennt diese Zertifikatnummer nicht.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El sistema no reconoce este número de certificado.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le système ne reconnaît pas ce numéro de certificat.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Het systeem herkent dit certificaatnummer niet")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Verify certificate number and re-enter.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Verify certificate number and re-enter.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie die Zertifikatnummer und geben Sie sie erneut ein.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Verifique el número de certificado y vuelva a introducirlo.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez le numéro de certificat et réessayez.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer het certificaatnummer en voer dit opnieuw in")); }
	};
}



