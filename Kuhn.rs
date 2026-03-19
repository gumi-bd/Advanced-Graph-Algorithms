fn try_kun(
    u: usize,
    graph: &Vec<Vec<usize>>,
    seen: &mut Vec<bool>,
    match_r: &mut Vec<Option<usize>>,
) -> bool {
    for &v in &graph[u] {
        if seen[v] {
            continue;
        }
        seen[v] = true;

        if match_r[v].is_none() || try_kun(match_r[v].unwrap(), graph, seen, match_r) {
            match_r[v] = Some(u);
            return true;
        }
    }
    false
}

fn max_bipartite_matching(graph: &Vec<Vec<usize>>, n: usize, m: usize) -> usize {
    let mut match_r = vec![None; m]; // match for right side
    let mut result = 0;

    for u in 0..n {
        let mut seen = vec![false; m];
        if try_kun(u, graph, &mut seen, &mut match_r) {
            result += 1;
        }
    }

    result
}

fn main() {
    // Example:
    // U = {0,1,2}, V = {0,1,2}
    // edges:
    // 0 -> [0,1]
    // 1 -> [1]
    // 2 -> [2]
    let graph = vec![
        vec![0, 1],
        vec![1],
        vec![2],
    ];

    let n = graph.len(); // size of U
    let m = 3;           // size of V

    let max_matching = max_bipartite_matching(&graph, n, m);

    println!("Maximum Matching: {}", max_matching);
}
