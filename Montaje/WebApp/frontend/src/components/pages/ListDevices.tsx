import Stack from 'react-bootstrap/Stack';
import Container from 'react-bootstrap/Container';
import Table from 'react-bootstrap/Table'
import Spinner from 'react-bootstrap/Spinner'
import { useDispatch, useSelector } from 'react-redux';
import { State } from '../../store';
import { useEffect } from 'react';
import { loadAllDevices } from '../../reducers/devices';
import LinkTo from '../LinkTo';

const ListDevicesPage = () => {
    const dispatch = useDispatch()
    const devices = useSelector((state: State) => (state.devices))

    useEffect(() => {
        dispatch(loadAllDevices())
        const interval = setInterval(() => {
            dispatch(loadAllDevices())
        }, 10000)
        return (() => {
            clearInterval(interval);
        })
    }, [dispatch])

    if (!devices.length) {
        return (
            <Container style={{ display: "grid", gridTemplate: "repeat(3, 1fr) / repeat(3, 1fr)", justifyItems: "center", alignItems: "center", flexGrow: 1 }}>
                <Spinner animation="border" role="status" style={{ gridRow: "2", gridColumn: "2" }}>
                    <span className="visually-hidden">Loading...</span>
                </Spinner>
            </Container>
        )
    }
    return (
        <Stack className='align-items-center'>
            <Table style={{ width: "50%", marginTop: "10%" }} striped bordered>
                <thead>
                    <tr>
                        <th>ID</th>
                        <th>Start Time</th>
                    </tr>
                </thead>
                <tbody>
                    {devices.map((e, i) => {
                        return (
                            <LinkTo to={`/info/${e.id}`} key={`link${i}`}>
                                <td key={`tdid${i}`}>{e.id}</td>
                                <td key={`tdtime${i}`}>{e.startTime}</td>
                            </LinkTo>
                        )
                    })}
                </tbody>
            </Table>
        </Stack>
    );
}

export default ListDevicesPage;