#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Infrastructure_diawdi_diawdi_logon_no_error : public CConditionObject
	{
	public:
		CBase_Infrastructure_diawdi_diawdi_logon_no_error() { }
		~CBase_Infrastructure_diawdi_diawdi_logon_no_error() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DIAWDI_LOGON_NO_ERROR")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("diawdi")); }
		virtual int GetSeverity() const { return 4; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("AWD logon was successful.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("AWD logon was successful.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("AWD-Anmeldung war erfolgreich.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La conexión con AWD fue exitosa.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Échec d'ouverture de session AWD")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Aanmelden bij AWD is gelukt")); }

        // Actions
	};
}



