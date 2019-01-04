#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dicbocore_err_invalid_time : public CConditionObject
	{
	public:
		CIFast_IFast_dicbocore_err_invalid_time() { }
		~CIFast_IFast_dicbocore_err_invalid_time() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_TIME")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dicbocore")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Transfers are not allowed between accounts of these tax types.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Transfers are not allowed between accounts of these tax types.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Transfers zwischen Konten dieser Steuerart sind nicht erlaubt.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se permiten transferencias entre cuentas de estos tipos tributarios.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Valeur de temps invalide. L'heure doit être en format HH:MM.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ongeldige waarde voor tijd, moet de indeling 'UU:MM' hebben")); }

        // Actions
	};
}



