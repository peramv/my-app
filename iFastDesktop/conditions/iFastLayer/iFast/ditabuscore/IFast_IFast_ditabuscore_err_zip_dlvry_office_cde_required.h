#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ditabuscore_err_zip_dlvry_office_cde_required : public CConditionObject
	{
	public:
		CIFast_IFast_ditabuscore_err_zip_dlvry_office_cde_required() { }
		~CIFast_IFast_ditabuscore_err_zip_dlvry_office_cde_required() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ZIP_DLVRY_OFFICE_CDE_REQUIRED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ditabuscore")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("At least two address lines are required.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Deux lignes d'adresse au moins sont requises, veuillez ressaisir.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Mindestens zwei Zeilen der Adresse sind erforderlich, bitte geben Sie neu ein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Se requieren al menos dos líneas de dirección; por favor vuelva a introducir los datos.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Au moins deux lignes d'adresse doivent être remplies.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er zijn ten minste twee adresregels vereist, vul deze opnieuw in")); }

        // Actions
	};
}



