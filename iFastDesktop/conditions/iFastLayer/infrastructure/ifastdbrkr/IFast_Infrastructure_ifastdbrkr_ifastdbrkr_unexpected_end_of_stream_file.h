#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastdbrkr_ifastdbrkr_unexpected_end_of_stream_file : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastdbrkr_ifastdbrkr_unexpected_end_of_stream_file() { }
		~CIFast_Infrastructure_ifastdbrkr_ifastdbrkr_unexpected_end_of_stream_file() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("IFASTDBRKR_UNEXPECTED_END_OF_STREAM_FILE")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The system does not recognize this tax ID number.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("The system does not recognize this tax ID number.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Das System erkennt diese Steuernummer nicht.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El sistema no reconoce este número de identificación tributaria.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le système ne reconnaît pas ce numéro de code d'imposition.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Het systeem herkent het nummer van dit belasting-ID niet")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Verify tax ID number and re-enter.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Verify tax ID number and re-enter.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie die Steuer-ID und geben Sie sie erneut ein.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Verify tax ID number and re-enter.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez le code d'impôt et réessayez.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer het nummer van de belasting-ID en voer dit opnieuw in")); }
	};
}



