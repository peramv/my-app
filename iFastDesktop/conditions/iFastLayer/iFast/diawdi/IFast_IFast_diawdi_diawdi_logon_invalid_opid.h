#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_diawdi_diawdi_logon_invalid_opid : public CConditionObject
	{
	public:
		CIFast_IFast_diawdi_diawdi_logon_invalid_opid() { }
		~CIFast_IFast_diawdi_diawdi_logon_invalid_opid() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DIAWDI_LOGON_INVALID_OPID")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("diawdi")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid social insurance number.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Invalid Social Insurance Number.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ungültige Sozialversicherungsnummer. Bitte geben Sie neu ein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Número de Seguro Social no válido. Por favor vuelva a introducir los datos.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Numéro d'assurance sociale invalide")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ongeldig Sofi-nummer. Vul het opnieuw in")); }

        // Actions
	};
}



