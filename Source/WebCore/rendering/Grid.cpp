/*
 * Copyright (C) 2017 Igalia S.L.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "config.h"
#include "Grid.h"

#include "GridArea.h"
#include "RenderGrid.h"

namespace WebCore {

Grid::Grid(RenderGrid& grid)
    : m_orderIterator(grid)
{
}

unsigned Grid::numTracks(GridTrackSizingDirection direction) const
{
    if (direction == GridTrackSizingDirection::ForRows)
        return m_grid.size();
    return m_grid.size() ? m_grid[0].size() : 0;
}

void Grid::ensureGridSize(unsigned maximumRowSize, unsigned maximumColumnSize)
{
    ASSERT(static_cast<int>(maximumRowSize) < GridPosition::max() * 2);
    ASSERT(static_cast<int>(maximumColumnSize) < GridPosition::max() * 2);
    const size_t oldColumnSize = numTracks(GridTrackSizingDirection::ForColumns);
    const size_t oldRowSize = numTracks(GridTrackSizingDirection::ForRows);
    if (maximumRowSize > oldRowSize) {
        m_grid.grow(maximumRowSize);
    }

    // Just grow the first row for now so that we know the requested size,
    // and we'll lazily allocate the others when they get used.
    if (maximumColumnSize > oldColumnSize && maximumRowSize) {
        m_grid[0].grow(maximumColumnSize);
    }
}

void Grid::ensureStorageForRow(unsigned row)
{
    m_grid[row].grow(m_grid[0].size());
}

GridArea Grid::insert(RenderBox& child, const GridArea& area)
{
    GridArea clampedArea = area;
    if (m_maxRows)
        clampedArea.rows.clamp(m_maxRows);
    if (m_maxColumns)
        clampedArea.columns.clamp(m_maxColumns);

    ASSERT(clampedArea.rows.isTranslatedDefinite() && clampedArea.columns.isTranslatedDefinite());
    ensureGridSize(clampedArea.rows.endLine(), clampedArea.columns.endLine());

    for (auto row : clampedArea.rows) {
        ensureStorageForRow(row);
        for (auto column : clampedArea.columns)
            m_grid[row][column].append(child);
    }

    setGridItemArea(child, clampedArea);
    return clampedArea;
}

const GridCell& Grid::cell(unsigned row, unsigned column) const
{
    // Storage for rows other than the first is lazily allocated. We can
    // just return a fake entry if the request is outside the allocated area,
    // since it must be empty.
    static const NeverDestroyed<GridCell> emptyCell;
    if (row && m_grid[row].size() <= column)
        return emptyCell;

    return m_grid[row][column];
}

void Grid::setExplicitGridStart(unsigned rowStart, unsigned columnStart)
{
    m_explicitRowStart = rowStart;
    m_explicitColumnStart = columnStart;
}

unsigned Grid::explicitGridStart(GridTrackSizingDirection direction) const
{
    return direction == GridTrackSizingDirection::ForRows ? m_explicitRowStart : m_explicitColumnStart;
}

void Grid::setClampingForSubgrid(unsigned maxRows, unsigned maxColumns)
{
    m_maxRows = maxRows;
    m_maxColumns = maxColumns;
}

void Grid::clampAreaToSubgridIfNeeded(GridArea& area)
{
    if (!area.rows.isIndefinite()) {
        if (m_maxRows)
            area.rows.clamp(m_maxRows);
    }
    if (!area.columns.isIndefinite()) {
        if (m_maxColumns)
            area.columns.clamp(m_maxColumns);
    }
}

GridArea Grid::gridItemArea(const RenderBox& item) const
{
    ASSERT(m_gridItemArea.contains(item));
    return m_gridItemArea.get(item);
}

void Grid::setGridItemArea(const RenderBox& item, GridArea area)
{
    m_gridItemArea.set(item, area);
}

void Grid::setAutoRepeatTracks(unsigned autoRepeatRows, unsigned autoRepeatColumns)
{
    ASSERT(static_cast<unsigned>(GridPosition::max()) >= numTracks(GridTrackSizingDirection::ForRows) + autoRepeatRows);
    ASSERT(static_cast<unsigned>(GridPosition::max()) >= numTracks(GridTrackSizingDirection::ForColumns) + autoRepeatColumns);
    m_autoRepeatRows = autoRepeatRows;
    m_autoRepeatColumns =  autoRepeatColumns;
}

unsigned Grid::autoRepeatTracks(GridTrackSizingDirection direction) const
{
    return direction == GridTrackSizingDirection::ForRows ? m_autoRepeatRows : m_autoRepeatColumns;
}

void Grid::setAutoRepeatEmptyColumns(std::unique_ptr<OrderedTrackIndexSet> autoRepeatEmptyColumns)
{
    ASSERT(!autoRepeatEmptyColumns || (autoRepeatEmptyColumns->size() <= m_autoRepeatColumns));
    m_autoRepeatEmptyColumns = WTFMove(autoRepeatEmptyColumns);
}

void Grid::setAutoRepeatEmptyRows(std::unique_ptr<OrderedTrackIndexSet> autoRepeatEmptyRows)
{
    ASSERT(!autoRepeatEmptyRows || (autoRepeatEmptyRows->size() <= m_autoRepeatRows));
    m_autoRepeatEmptyRows = WTFMove(autoRepeatEmptyRows);
}

bool Grid::hasAutoRepeatEmptyTracks(GridTrackSizingDirection direction) const
{
    return direction == GridTrackSizingDirection::ForColumns ? !!m_autoRepeatEmptyColumns : !!m_autoRepeatEmptyRows;
}

bool Grid::isEmptyAutoRepeatTrack(GridTrackSizingDirection direction, unsigned line) const
{
    ASSERT(hasAutoRepeatEmptyTracks(direction));
    return autoRepeatEmptyTracks(direction)->contains(line);
}

OrderedTrackIndexSet* Grid::autoRepeatEmptyTracks(GridTrackSizingDirection direction) const
{
    ASSERT(hasAutoRepeatEmptyTracks(direction));
    return direction == GridTrackSizingDirection::ForColumns ? m_autoRepeatEmptyColumns.get() : m_autoRepeatEmptyRows.get();
}

GridSpan Grid::gridItemSpan(const RenderBox& gridItem, GridTrackSizingDirection direction) const
{
    GridArea area = gridItemArea(gridItem);
    return direction == GridTrackSizingDirection::ForColumns ? area.columns : area.rows;
}

GridSpan Grid::gridItemSpanIgnoringCollapsedTracks(const RenderBox& gridItem, GridTrackSizingDirection direction) const
{
    auto span = gridItemSpan(gridItem, direction);
    if (!span.startLine() || !hasAutoRepeatEmptyTracks(direction))
        return span;
    unsigned currentLine = span.startLine() - 1;

    while (currentLine && isEmptyAutoRepeatTrack(direction, currentLine))
        currentLine--;
    if (currentLine)
        return GridSpan::translatedDefiniteGridSpan(currentLine + 1, span.integerSpan());

    // Still need to check if the first track is empty
    return isEmptyAutoRepeatTrack(direction, currentLine) ? GridSpan::translatedDefiniteGridSpan(currentLine, span.integerSpan()) : GridSpan::translatedDefiniteGridSpan(currentLine + 1, span.integerSpan());
}

void Grid::setupGridForMasonryLayout()
{
    // FIXME(248472): See if we can resize grid instead of clearing it here: https://bugs.webkit.org/show_bug.cgi?id=248472
    m_grid.clear();
    m_gridItemArea.clear();
}

void Grid::setNeedsItemsPlacement(bool needsItemsPlacement)
{
    m_needsItemsPlacement = needsItemsPlacement;

    if (!needsItemsPlacement) {
        m_grid.shrinkToFit();
        return;
    }

    m_grid.shrink(0);
    m_gridItemArea.clear();
    m_explicitRowStart = 0;
    m_explicitColumnStart = 0;
    m_autoRepeatEmptyColumns = nullptr;
    m_autoRepeatEmptyRows = nullptr;
    m_autoRepeatColumns = 0;
    m_autoRepeatRows = 0;
    m_maxColumns = 0;
    m_maxRows = 0;
}

GridIterator::GridIterator(const Grid& grid, GridTrackSizingDirection direction, unsigned fixedTrackIndex, unsigned varyingTrackIndex)
    : m_grid(grid)
    , m_direction(direction)
    , m_rowIndex((direction == GridTrackSizingDirection::ForColumns) ? varyingTrackIndex : fixedTrackIndex)
    , m_columnIndex((direction == GridTrackSizingDirection::ForColumns) ? fixedTrackIndex : varyingTrackIndex)
    , m_childIndex(0)
{
    if (m_grid.maxRows()) {
        ASSERT(m_grid.numTracks(GridTrackSizingDirection::ForRows));
        ASSERT(m_rowIndex < m_grid.numTracks(GridTrackSizingDirection::ForRows));
    }
    if (m_grid.maxColumns()) {
        ASSERT(m_grid.numTracks(GridTrackSizingDirection::ForColumns));
        ASSERT(m_columnIndex < m_grid.numTracks(GridTrackSizingDirection::ForColumns));
    }
}

RenderBox* GridIterator::nextGridItem()
{
    if (m_grid.maxRows())
        ASSERT(m_grid.numTracks(GridTrackSizingDirection::ForRows));
    if (m_grid.maxColumns())
        ASSERT(m_grid.numTracks(GridTrackSizingDirection::ForColumns));
    unsigned& varyingTrackIndex = (m_direction == GridTrackSizingDirection::ForColumns) ? m_rowIndex : m_columnIndex;
    const unsigned endOfVaryingTrackIndex = (m_direction == GridTrackSizingDirection::ForColumns) ? m_grid.numTracks(GridTrackSizingDirection::ForRows) : m_grid.numTracks(GridTrackSizingDirection::ForColumns);
    for (; varyingTrackIndex < endOfVaryingTrackIndex; ++varyingTrackIndex) {
        const auto& children = m_grid.cell(m_rowIndex, m_columnIndex);
        if (m_childIndex < children.size())
            return children[m_childIndex++].get();

        m_childIndex = 0;
    }
    return 0;
}

bool GridIterator::isEmptyAreaEnough(unsigned rowSpan, unsigned columnSpan) const
{
    if (m_grid.maxRows())
        ASSERT(m_grid.numTracks(GridTrackSizingDirection::ForRows));
    if (m_grid.maxColumns())
        ASSERT(m_grid.numTracks(GridTrackSizingDirection::ForColumns));
    // Ignore cells outside current grid as we will grow it later if needed.
    unsigned maxRows = std::min<unsigned>(m_rowIndex + rowSpan, m_grid.numTracks(GridTrackSizingDirection::ForRows));
    unsigned maxColumns = std::min<unsigned>(m_columnIndex + columnSpan, m_grid.numTracks(GridTrackSizingDirection::ForColumns));

    // This adds a O(N^2) behavior that shouldn't be a big deal as we expect spanning areas to be small.
    for (unsigned row = m_rowIndex; row < maxRows; ++row) {
        for (unsigned column = m_columnIndex; column < maxColumns; ++column) {
            auto& children = m_grid.cell(row, column);
            if (!children.isEmpty())
                return false;
        }
    }

    return true;
}

std::optional<GridArea> GridIterator::nextEmptyGridArea(unsigned fixedTrackSpan, unsigned varyingTrackSpan)
{
    if (m_grid.maxRows())
        ASSERT(m_grid.numTracks(GridTrackSizingDirection::ForRows));
    if (m_grid.maxColumns())
        ASSERT(m_grid.numTracks(GridTrackSizingDirection::ForColumns));
    ASSERT(fixedTrackSpan >= 1);
    ASSERT(varyingTrackSpan >= 1);

    if (!m_grid.hasGridItems())
        return { };

    unsigned rowSpan = (m_direction == GridTrackSizingDirection::ForColumns) ? varyingTrackSpan : fixedTrackSpan;
    unsigned columnSpan = (m_direction == GridTrackSizingDirection::ForColumns) ? fixedTrackSpan : varyingTrackSpan;

    unsigned& varyingTrackIndex = (m_direction == GridTrackSizingDirection::ForColumns) ? m_rowIndex : m_columnIndex;
    const unsigned endOfVaryingTrackIndex = (m_direction == GridTrackSizingDirection::ForColumns) ? m_grid.numTracks(GridTrackSizingDirection::ForRows) : m_grid.numTracks(GridTrackSizingDirection::ForColumns);
    for (; varyingTrackIndex < endOfVaryingTrackIndex; ++varyingTrackIndex) {
        if (isEmptyAreaEnough(rowSpan, columnSpan)) {
            auto result = GridArea { GridSpan::translatedDefiniteGridSpan(m_rowIndex, m_rowIndex + rowSpan), GridSpan::translatedDefiniteGridSpan(m_columnIndex, m_columnIndex + columnSpan) };
            // Advance the iterator to avoid an infinite loop where we would return the same grid area over and over.
            ++varyingTrackIndex;
            return result;
        }
    }
    return { };
}

GridIterator GridIterator::createForSubgrid(const RenderGrid& subgrid, const GridIterator& outer, GridSpan subgridSpanInOuter)
{
    ASSERT(subgrid.isSubgridInParentDirection(outer.direction()));
    CheckedPtr parent = downcast<RenderGrid>(subgrid.parent());

    // Translate the current row/column indices into the coordinate
    // space of the subgrid.
    unsigned fixedIndex = (outer.direction() == GridTrackSizingDirection::ForColumns) ? outer.m_columnIndex : outer.m_rowIndex;
    fixedIndex -= subgridSpanInOuter.startLine();

    auto innerDirection = GridLayoutFunctions::flowAwareDirectionForChild(*parent, subgrid, outer.direction());
    ASSERT(subgrid.isSubgrid(innerDirection));

    if (GridLayoutFunctions::isSubgridReversedDirection(*parent, outer.direction(), subgrid)) {
        unsigned fixedMax = subgrid.currentGrid().numTracks(innerDirection);
        fixedIndex = fixedMax - fixedIndex - 1;
    }

    return GridIterator(subgrid.currentGrid(), innerDirection, fixedIndex);
}

} // namespace WebCore
