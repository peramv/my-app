#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_invalid_dlr_br_summary : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_invalid_dlr_br_summary() { }
		~CIFast_IFast_dita2kdb_dita2kdb_invalid_dlr_br_summary() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_INVALID_DLR_BR_SUMMARY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Entity not associated with an acoount.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Entity not associated with an acoount.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Objekt nicht mit einem Konto verbunden")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La entidad no está asociada a una cuenta")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'entité n'est associée à aucun compte.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Eenheid hoort niet bij een account")); }

        // Actions
	};
}



