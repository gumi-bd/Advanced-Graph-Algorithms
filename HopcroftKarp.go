package main

import (
	"fmt"
)

const INF = int(1e9)

type HopcroftKarp struct {
	n, m int
	adj  [][]int

	pairU []int
	pairV []int
	dist  []int
}

func NewHopcroftKarp(n, m int) *HopcroftKarp {
	hk := &HopcroftKarp{
		n:     n,
		m:     m,
		adj:   make([][]int, n),
		pairU: make([]int, n),
		pairV: make([]int, m),
		dist:  make([]int, n),
	}

	for i := 0; i < n; i++ {
		hk.pairU[i] = -1
	}
	for i := 0; i < m; i++ {
		hk.pairV[i] = -1
	}

	return hk
}

func (hk *HopcroftKarp) AddEdge(u, v int) {
	hk.adj[u] = append(hk.adj[u], v)
}

func (hk *HopcroftKarp) bfs() bool {
	queue := []int{}

	for u := 0; u < hk.n; u++ {
		if hk.pairU[u] == -1 {
			hk.dist[u] = 0
			queue = append(queue, u)
		} else {
			hk.dist[u] = INF
		}
	}

	foundAugPath := false

	for len(queue) > 0 {
		u := queue[0]
		queue = queue[1:]

		for _, v := range hk.adj[u] {
			if hk.pairV[v] != -1 && hk.dist[hk.pairV[v]] == INF {
				hk.dist[hk.pairV[v]] = hk.dist[u] + 1
				queue = append(queue, hk.pairV[v])
			}
			if hk.pairV[v] == -1 {
				foundAugPath = true
			}
		}
	}

	return foundAugPath
}

func (hk *HopcroftKarp) dfs(u int) bool {
	for _, v := range hk.adj[u] {
		if hk.pairV[v] == -1 ||
			(hk.dist[hk.pairV[v]] == hk.dist[u]+1 && hk.dfs(hk.pairV[v])) {

			hk.pairU[u] = v
			hk.pairV[v] = u
			return true
		}
	}
	hk.dist[u] = INF
	return false
}

func (hk *HopcroftKarp) MaxMatching() int {
	result := 0

	for hk.bfs() {
		for u := 0; u < hk.n; u++ {
			if hk.pairU[u] == -1 && hk.dfs(u) {
				result++
			}
		}
	}

	return result
}

func main() {
	// Example:
	// U = {0,1,2}, V = {0,1,2}
	hk := NewHopcroftKarp(3, 3)

	hk.AddEdge(0, 0)
	hk.AddEdge(0, 1)
	hk.AddEdge(1, 1)
	hk.AddEdge(2, 2)

	fmt.Println("Maximum Matching:", hk.MaxMatching())
}
