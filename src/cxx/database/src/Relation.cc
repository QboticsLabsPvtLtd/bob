/**
 * @file src/Relation.cc
 * @author <a href="mailto:andre.anjos@idiap.ch">Andre Anjos</a> 
 *
 * @brief Implementation of relations 
 */

#include "database/Relation.h"

namespace db = Torch::database;

db::Relation::Relation (boost::shared_ptr<std::map<size_t,std::string> > id_role): 
  m_id(0), 
  m_id_role(id_role)
{ 
}

db::Relation::~Relation() {
}

void db::Relation::append( boost::shared_ptr<db::Member> member) {
  size_t_pair ids( member->getArrayId(), member->getArraysetId());
  m_member.insert( std::pair<size_t_pair,boost::shared_ptr<Member> >(
        ids, member) );
}
