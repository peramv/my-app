#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_del_rec_not_found : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_del_rec_not_found() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_del_rec_not_found() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_DEL_REC_NOT_FOUND")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Allocation must be entered if corresponding fund and class are blank.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Allocation must be entered if corresponding fund and class are blank.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Zuweisung muss eingegeben werden, wenn der entsprechende Fonds und die Klasse leer sind.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Debe introducirse la asignación si el fondo y clase correspondientes están en blanco")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le champ Répartition doit être rempli si les champs Fonds et Classe correspondants ne le sont pas.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Allocatie moet worden ingevoerd als bijbehorende fonds en categorie leeg zijn")); }

        // Actions
	};
}



