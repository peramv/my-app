#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_a90_rec_not_found : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_a90_rec_not_found() { }
		~CIFast_IFast_dita2kdb_dita2kdb_a90_rec_not_found() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_A90_REC_NOT_FOUND")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Unable to add a record, address code already exists.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Unable to add a record, address code already exists.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Eintrag kann nicht hinzugefügt werden, Adresscode existiert bereits")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Imposible añadir un registro. El código de dirección ya existe.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Impossible d'ajouter un enregistrement, le code d'adresse existe déjà.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Record kan niet worden toegevoegd, de adrescode bestaat al")); }

        // Actions
	};
}



