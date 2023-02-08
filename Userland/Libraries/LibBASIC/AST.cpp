/*
 * Copyright (c) 2023, Florian Kaiser <mail@floriankaiser.org>
 * Copyright (c) 2023, Fabian Neundorf <CommodoreFabianus@gmx.de>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include "AST.h"

namespace basic {

ASTNode::~ASTNode() { }

void AST::dump() const
{
    for (auto& node : m_nodes) {
        node.dump();
    }
}

size_t AST::size() const
{
    size_t size = 0;
    for (auto& node : m_nodes) {
        size += node.size();
    }
    return size;
}

}
