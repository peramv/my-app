#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_no_crp_set : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_no_crp_set() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_no_crp_set() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_NO_CRP_SET")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Date of birth for Annuitant is mandatory for contracts.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Date of birth for Annuitant is mandatory for contracts.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Geburtsdatum des Rentenempfängers ist  für Verträge obligatorisch")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La fecha de nacimiento del titular de la anualidad es obligatoria para los contratos")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date de naissance du crédirentier est requise pour les contrats.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Geboortedatum lijfrentetrekker is verplicht voor overeenkomsten")); }

        // Actions
	};
}



