let ctx = document.getElementById('chart').getContext('2d');
let chart = new Chart(ctx, {
  type: 'bar',
  data: {
    labels: ['2020/Q1', '2020/Q2', '2020/Q3', '2020/Q4'],
    datasets: [
      {
        label: 'Gross volume ($)',
        backgroundColor: '#79AEC8',
        borderColor: '#417690',
        data: [26900, 28700, 27300, 29200],
      },
    ],
  },
  options: {
    title: {
      text: 'Gross Volume in 2020',
      display: true,
    },
  },
});
