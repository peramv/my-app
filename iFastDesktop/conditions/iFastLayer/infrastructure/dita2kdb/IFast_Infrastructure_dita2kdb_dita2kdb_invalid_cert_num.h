#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_dita2kdb_dita2kdb_invalid_cert_num : public CConditionObject
	{
	public:
		CIFast_Infrastructure_dita2kdb_dita2kdb_invalid_cert_num() { }
		~CIFast_Infrastructure_dita2kdb_dita2kdb_invalid_cert_num() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_INVALID_CERT_NUM")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

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



