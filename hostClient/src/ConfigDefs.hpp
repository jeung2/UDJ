/**
 * Copyright 2011 Kurtis L. Nusbaum
 * 
 * This file is part of UDJ.
 * 
 * UDJ is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 * 
 * UDJ is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with UDJ.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef CONFIG_DEFS_HPP
#define CONFIG_DEFS_HPP
#include <QUrl>

namespace UDJ{

typedef long playlist_song_id_t;
typedef long library_song_id_t;
typedef long playlist_id_t;
typedef long event_id_t;
typedef long user_id_t;
typedef int lib_sync_status_t;
typedef int avail_music_sync_status_t;
typedef int playlist_add_sync_status_t;
typedef int playlist_remove_sync_status_t;
typedef long client_request_id_t;
typedef long song_list_id_t;
typedef long song_list_entry_id_t;

} //end namespace

#ifdef UDJ_DEBUG_BUILD
#include <iostream>
#include <QSqlError>

#define EXEC_SQL( MESSAGE , STMT, QSQLOBJECT ) \
	if(!( STMT )){ \
		std::cerr << MESSAGE << " IN FILE " << __FILE__ << " AT LINE " \
      << __LINE__ <<  std::endl; \
		std::cerr << "SQL ERROR MESSAGE: '" << \
      QSQLOBJECT.lastError().text().toStdString() << "'" << std::endl; \
    std::cerr << "QUERY WAS: '" << QSQLOBJECT.lastQuery().toStdString() \
      << "'" <<std::endl; \
		std::cerr << std::endl; \
	} \

#define EXEC_INSERT( MESSAGE, QSQLOBJECT, RESULT_VAR, RESULT_VAR_TYPE) \
  QSQLOBJECT.exec(); \
  if( QSQLOBJECT.lastError().type() != QSqlError::NoError ){ \
		std::cerr << MESSAGE << " IN FILE " << __FILE__ << " AT LINE " \
      << __LINE__ <<  std::endl; \
		std::cerr << "SQL ERROR MESSAGE: '" << \
    QSQLOBJECT.lastError().text().toStdString() << "'" << std::endl; \
    std::cerr << "QUERY WAS: '" << QSQLOBJECT.lastQuery().toStdString() \
      << "'" <<std::endl; \
		std::cerr << std::endl; \
  } \
  else{ \
    RESULT_VAR = QSQLOBJECT.lastInsertId().value< RESULT_VAR_TYPE >(); \
  }

#define EXEC_BULK_QUERY( MESSAGE, QSQLOBJECT) \
  if(!QSQLOBJECT.execBatch()){ \
		std::cerr << MESSAGE << " IN FILE " << __FILE__ << " AT LINE " \
      << __LINE__ <<  std::endl; \
		std::cerr << "SQL ERROR MESSAGE: '" << \
    QSQLOBJECT.lastError().text().toStdString() << "'" << std::endl; \
    std::cerr << "QUERY WAS: '" << QSQLOBJECT.lastQuery().toStdString() \
      << "'" <<std::endl; \
		std::cerr << std::endl; \
  } \

#define DEBUG_MESSAGE( MESSAGE ) \
  std::cout << MESSAGE << std::endl;

#else

#define EXEC_SQL( MESSAGE, STMT, QSQLOBJECT) \
	STMT;

#define EXEC_INSERT( MESSAGE, QSQLOBJECT, RESULT_VAR) \
  QSQLOBJECT.exec(); \
  RESULT_VAR = QSQLOBJECT.lastInsertId().value<library_song_id_t>();

#define DEBUG_MESSAGE( MESSAGE )

#define EXEC_BULK_QUERY( MESSAGE, QSQLOBJECT) \
  QSQLOBJECT.execBatch();

#endif


#endif //CONFIG_DEFS_HPP
