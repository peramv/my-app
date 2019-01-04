#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_day_cde : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_day_cde() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_day_cde() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_INVALID_DAY_CDE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Institution Code exceeds allowable number of digits.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Institution Code exceeds allowable number of digits.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Der Institutscode überschreitet die erlaubte Anzahl der Ziffern.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El código de institución excede la cantidad de dígitos permitida")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le code d'institution excède le nombre de caractères numériques autorisé.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Instellingscode overschrijdt toegestane aantal cijfers")); }

        // Actions
	};
}



